//
// kqueue_reactor.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2005 Stefan Arentz (stefan at soze dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_KQUEUE_REACTOR_HPP
#define BOOST_ASIO_DETAIL_KQUEUE_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/kqueue_reactor_fwd.hpp>

#if defined(BOOST_ASIO_HAS_KQUEUE)

#include <boost/asio/detail/push_options.hpp>
#include <cstddef>
#include <vector>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <boost/config.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/throw_exception.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/error.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/task_io_service.hpp>
#include <boost/asio/detail/thread.hpp>
#include <boost/asio/detail/reactor_op_queue.hpp>
#include <boost/asio/detail/select_interrupter.hpp>
#include <boost/asio/detail/service_base.hpp>
#include <boost/asio/detail/signal_blocker.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/timer_queue.hpp>

// Older versions of Mac OS X may not define EV_OOBAND.
#if !defined(EV_OOBAND)
# define EV_OOBAND EV_FLAG1
#endif // !defined(EV_OOBAND)

namespace boost {
namespace asio {
namespace detail {

template <bool Own_Thread>
class kqueue_reactor
  : public boost::asio::detail::service_base<kqueue_reactor<Own_Thread> >
{
public:
  // Per-descriptor data.
  struct per_descriptor_data
  {
    bool allow_speculative_read;
    bool allow_speculative_write;
  };

  // Constructor.
  kqueue_reactor(boost::asio::io_service& io_service)
    : boost::asio::detail::service_base<
        kqueue_reactor<Own_Thread> >(io_service),
      mutex_(),
      kqueue_fd_(do_kqueue_create()),
      wait_in_progress_(false),
      interrupter_(),
      read_op_queue_(),
      write_op_queue_(),
      except_op_queue_(),
      pending_cancellations_(),
      stop_thread_(false),
      thread_(0),
      shutdown_(false),
      need_kqueue_wait_(true)
  {
    // Start the reactor's internal thread only if needed.
    if (Own_Thread)
    {
      boost::asio::detail::signal_blocker sb;
      thread_ = new boost::asio::detail::thread(
          bind_handler(&kqueue_reactor::call_run_thread, this));
    }

    // Add the interrupter's descriptor to the kqueue.
    struct kevent event;
    EV_SET(&event, interrupter_.read_descriptor(),
        EVFILT_READ, EV_ADD, 0, 0, 0);
    ::kevent(kqueue_fd_, &event, 1, 0, 0, 0);
  }

  // Destructor.
  ~kqueue_reactor()
  {
    shutdown_service();
    close(kqueue_fd_);
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown_service()
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    shutdown_ = true;
    stop_thread_ = true;
    lock.unlock();

    if (thread_)
    {
      interrupter_.interrupt();
      thread_->join();
      delete thread_;
      thread_ = 0;
    }

    read_op_queue_.destroy_operations();
    write_op_queue_.destroy_operations();
    except_op_queue_.destroy_operations();

    for (std::size_t i = 0; i < timer_queues_.size(); ++i)
      timer_queues_[i]->destroy_timers();
    timer_queues_.clear();
  }

  // Initialise the task, but only if the reactor is not in its own thread.
  void init_task()
  {
    if (!Own_Thread)
    {
      typedef task_io_service<kqueue_reactor<Own_Thread> > task_io_service_type;
      use_service<task_io_service_type>(this->get_io_service()).init_task();
    }
  }

  // Register a socket with the reactor. Returns 0 on success, system error
  // code on failure.
  int register_descriptor(socket_type, per_descriptor_data& descriptor_data)
  {
    descriptor_data.allow_speculative_read = true;
    descriptor_data.allow_speculative_write = true;

    return 0;
  }

  // Start a new read operation. The handler object will be invoked when the
  // given descriptor is ready to be read, or an error has occurred.
  template <typename Handler>
  void start_read_op(socket_type descriptor,
      per_descriptor_data& descriptor_data, Handler handler,
      bool allow_speculative_read = true)
  {
    if (allow_speculative_read && descriptor_data.allow_speculative_read)
    {
      boost::system::error_code ec;
      std::size_t bytes_transferred = 0;
      if (handler.perform(ec, bytes_transferred))
      {
        handler.complete(ec, bytes_transferred);
        return;
      }

      // We only get one shot at a speculative read in this function.
      allow_speculative_read = false;
    }

    boost::asio::detail::mutex::scoped_lock lock(mutex_);

    if (shutdown_)
      return;

    if (!allow_speculative_read)
      need_kqueue_wait_ = true;
    else if (!read_op_queue_.has_operation(descriptor))
    {
      // Speculative reads are ok as there are no queued read operations.
      descriptor_data.allow_speculative_read = true;

      boost::system::error_code ec;
      std::size_t bytes_transferred = 0;
      if (handler.perform(ec, bytes_transferred))
      {
        handler.complete(ec, bytes_transferred);
        return;
      }
    }

    // Speculative reads are not ok as there will be queued read operations.
    descriptor_data.allow_speculative_read = false;

    if (read_op_queue_.enqueue_operation(descriptor, handler))
    {
      struct kevent event;
      EV_SET(&event, descriptor, EVFILT_READ, EV_ADD, 0, 0, 0);
      if (::kevent(kqueue_fd_, &event, 1, 0, 0, 0) == -1)
      {
        boost::system::error_code ec(errno,
            boost::asio::error::get_system_category());
        read_op_queue_.perform_all_operations(descriptor, ec);
      }
    }
  }

  // Start a new write operation. The handler object will be invoked when the
  // given descriptor is ready to be written, or an error has occurred.
  template <typename Handler>
  void start_write_op(socket_type descriptor,
      per_descriptor_data& descriptor_data, Handler handler,
      bool allow_speculative_write = true)
  {
    if (allow_speculative_write && descriptor_data.allow_speculative_write)
    {
      boost::system::error_code ec;
      std::size_t bytes_transferred = 0;
      if (handler.perform(ec, bytes_transferred))
      {
        handler.complete(ec, bytes_transferred);
        return;
      }

      // We only get one shot at a speculative write in this function.
      allow_speculative_write = false;
    }

    boost::asio::detail::mutex::scoped_lock lock(mutex_);

    if (shutdown_)
      return;

    if (!allow_speculative_write)
      need_kqueue_wait_ = true;
    else if (!write_op_queue_.has_operation(descriptor))
    {
      // Speculative writes are ok as there are no queued write operations.
      descriptor_data.allow_speculative_write = true;

      boost::system::error_code ec;
      std::size_t bytes_transferred = 0;
      if (handler.perform(ec, bytes_transferred))
      {
        handler.complete(ec, bytes_transferred);
        return;
      }
    }

    // Speculative writes are not ok as there will be queued write operations.
    descriptor_data.allow_speculative_write = false;

    if (write_op_queue_.enqueue_operation(descriptor, handler))
    {
      struct kevent event;
      EV_SET(&event, descriptor, EVFILT_WRITE, EV_ADD, 0, 0, 0);
      if (::kevent(kqueue_fd_, &event, 1, 0, 0, 0) == -1)
      {
        boost::system::error_code ec(errno,
            boost::asio::error::get_system_category());
        write_op_queue_.perform_all_operations(descriptor, ec);
      }
    }
  }

  // Start a new exception operation. The handler object will be invoked when
  // the given descriptor has exception information, or an error has occurred.
  template <typename Handler>
  void start_except_op(socket_type descriptor,
      per_descriptor_data&, Handler handler)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);

    if (shutdown_)
      return;

    if (except_op_queue_.enqueue_operation(descriptor, handler))
    {
      struct kevent event;
      if (read_op_queue_.has_operation(descriptor))
        EV_SET(&event, descriptor, EVFILT_READ, EV_ADD, 0, 0, 0);
      else
        EV_SET(&event, descriptor, EVFILT_READ, EV_ADD, EV_OOBAND, 0, 0);
      if (::kevent(kqueue_fd_, &event, 1, 0, 0, 0) == -1)
      {
        boost::system::error_code ec(errno,
            boost::asio::error::get_system_category());
        except_op_queue_.perform_all_operations(descriptor, ec);
      }
    }
  }

  // Start a new write operation. The handler object will be invoked when the
  // given descriptor is ready to be written, or an error has occurred.
  template <typename Handler>
  void start_connect_op(socket_type descriptor,
      per_descriptor_data& descriptor_data, Handler handler)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);

    if (shutdown_)
      return;

    // Speculative writes are not ok as there will be queued write operations.
    descriptor_data.allow_speculative_write = false;

    if (write_op_queue_.enqueue_operation(descriptor, handler))
    {
      struct kevent event;
      EV_SET(&event, descriptor, EVFILT_WRITE, EV_ADD, 0, 0, 0);
      if (::kevent(kqueue_fd_, &event, 1, 0, 0, 0) == -1)
      {
        boost::system::error_code ec(errno,
            boost::asio::error::get_system_category());
        write_op_queue_.perform_all_operations(descriptor, ec);
      }
    }
  }

  // Cancel all operations associated with the given descriptor. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  void cancel_ops(socket_type descriptor, per_descriptor_data&)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    cancel_ops_unlocked(descriptor);
  }

  // Cancel any operations that are running against the descriptor and remove
  // its registration from the reactor.
  void close_descriptor(socket_type descriptor, per_descriptor_data&)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);

    // Remove the descriptor from kqueue.
    struct kevent event[2];
    EV_SET(&event[0], descriptor, EVFILT_READ, EV_DELETE, 0, 0, 0);
    EV_SET(&event[1], descriptor, EVFILT_WRITE, EV_DELETE, 0, 0, 0);
    ::kevent(kqueue_fd_, event, 2, 0, 0, 0);
    
    // Cancel any outstanding operations associated with the descriptor.
    cancel_ops_unlocked(descriptor);
  }

  // Add a new timer queue to the reactor.
  template <typename Time_Traits>
  void add_timer_queue(timer_queue<Time_Traits>& timer_queue)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    timer_queues_.push_back(&timer_queue);
  }

  // Remove a timer queue from the reactor.
  template <typename Time_Traits>
  void remove_timer_queue(timer_queue<Time_Traits>& timer_queue)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    for (std::size_t i = 0; i < timer_queues_.size(); ++i)
    {
      if (timer_queues_[i] == &timer_queue)
      {
        timer_queues_.erase(timer_queues_.begin() + i);
        return;
      }
    }
  }

  // Schedule a timer in the given timer queue to expire at the specified
  // absolute time. The handler object will be invoked when the timer expires.
  template <typename Time_Traits, typename Handler>
  void schedule_timer(timer_queue<Time_Traits>& timer_queue,
      const typename Time_Traits::time_type& time, Handler handler, void* token)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    if (!shutdown_)
      if (timer_queue.enqueue_timer(time, handler, token))
        interrupter_.interrupt();
  }

  // Cancel the timer associated with the given token. Returns the number of
  // handlers that have been posted or dispatched.
  template <typename Time_Traits>
  std::size_t cancel_timer(timer_queue<Time_Traits>& timer_queue, void* token)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    std::size_t n = timer_queue.cancel_timer(token);
    if (n > 0)
      interrupter_.interrupt();
    return n;
  }

private:
  friend class task_io_service<kqueue_reactor<Own_Thread> >;

  // Run the kqueue loop.
  void run(bool block)
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);

    // Dispatch any operation cancellations that were made while the select
    // loop was not running.
    read_op_queue_.perform_cancellations();
    write_op_queue_.perform_cancellations();
    except_op_queue_.perform_cancellations();
    for (std::size_t i = 0; i < timer_queues_.size(); ++i)
      timer_queues_[i]->dispatch_cancellations();

    // Check if the thread is supposed to stop.
    if (stop_thread_)
    {
      complete_operations_and_timers(lock);
      return;
    }

    // We can return immediately if there's no work to do and the reactor is
    // not supposed to block.
    if (!block && read_op_queue_.empty() && write_op_queue_.empty()
        && except_op_queue_.empty() && all_timer_queues_are_empty())
    {
      complete_operations_and_timers(lock);
      return;
    }

    // Determine how long to block while waiting for events.
    timespec timeout_buf = { 0, 0 };
    timespec* timeout = block ? get_timeout(timeout_buf) : &timeout_buf;

    wait_in_progress_ = true;
    lock.unlock();

    // Block on the kqueue descriptor.
    struct kevent events[128];
    int num_events = (block || need_kqueue_wait_)
      ? kevent(kqueue_fd_, 0, 0, events, 128, timeout)
      : 0;

    lock.lock();
    wait_in_progress_ = false;

    // Block signals while performing operations.
    boost::asio::detail::signal_blocker sb;

    // Dispatch the waiting events.
    for (int i = 0; i < num_events; ++i)
    {
      int descriptor = events[i].ident;
      if (descriptor == interrupter_.read_descriptor())
      {
        interrupter_.reset();
      }
      else if (events[i].filter == EVFILT_READ)
      {
        // Dispatch operations associated with the descriptor.
        bool more_reads = false;
        bool more_except = false;
        if (events[i].flags & EV_ERROR)
        {
          boost::system::error_code error(
              events[i].data, boost::asio::error::get_system_category());
          except_op_queue_.perform_all_operations(descriptor, error);
          read_op_queue_.perform_all_operations(descriptor, error);
        }
        else if (events[i].flags & EV_OOBAND)
        {
          boost::system::error_code error;
          more_except = except_op_queue_.perform_operation(descriptor, error);
          if (events[i].data > 0)
            more_reads = read_op_queue_.perform_operation(descriptor, error);
          else
            more_reads = read_op_queue_.has_operation(descriptor);
        }
        else
        {
          boost::system::error_code error;
          more_reads = read_op_queue_.perform_operation(descriptor, error);
          more_except = except_op_queue_.has_operation(descriptor);
        }

        // Update the descriptor in the kqueue.
        struct kevent event;
        if (more_reads)
          EV_SET(&event, descriptor, EVFILT_READ, EV_ADD, 0, 0, 0);
        else if (more_except)
          EV_SET(&event, descriptor, EVFILT_READ, EV_ADD, EV_OOBAND, 0, 0);
        else
          EV_SET(&event, descriptor, EVFILT_READ, EV_DELETE, 0, 0, 0);
        if (::kevent(kqueue_fd_, &event, 1, 0, 0, 0) == -1)
        {
          boost::system::error_code error(errno,
              boost::asio::error::get_system_category());
          except_op_queue_.perform_all_operations(descriptor, error);
          read_op_queue_.perform_all_operations(descriptor, error);
        }
      }
      else if (events[i].filter == EVFILT_WRITE)
      {
        // Dispatch operations associated with the descriptor.
        bool more_writes = false;
        if (events[i].flags & EV_ERROR)
        {
          boost::system::error_code error(
              events[i].data, boost::asio::error::get_system_category());
          write_op_queue_.perform_all_operations(descriptor, error);
        }
        else
        {
          boost::system::error_code error;
          more_writes = write_op_queue_.perform_operation(descriptor, error);
        }

        // Update the descriptor in the kqueue.
        struct kevent event;
        if (more_writes)
          EV_SET(&event, descriptor, EVFILT_WRITE, EV_ADD, 0, 0, 0);
        else
          EV_SET(&event, descriptor, EVFILT_WRITE, EV_DELETE, 0, 0, 0);
        if (::kevent(kqueue_fd_, &event, 1, 0, 0, 0) == -1)
        {
          boost::system::error_code error(errno,
              boost::asio::error::get_system_category());
          write_op_queue_.perform_all_operations(descriptor, error);
        }
      }
    }

    read_op_queue_.perform_cancellations();
    write_op_queue_.perform_cancellations();
    except_op_queue_.perform_cancellations();
    for (std::size_t i = 0; i < timer_queues_.size(); ++i)
    {
      timer_queues_[i]->dispatch_timers();
      timer_queues_[i]->dispatch_cancellations();
    }

    // Issue any pending cancellations.
    for (std::size_t i = 0; i < pending_cancellations_.size(); ++i)
      cancel_ops_unlocked(pending_cancellations_[i]);
    pending_cancellations_.clear();

    // Determine whether kqueue needs to be called next time the reactor is run.
    need_kqueue_wait_ = !read_op_queue_.empty()
      || !write_op_queue_.empty() || !except_op_queue_.empty();

    complete_operations_and_timers(lock);
  }

  // Run the select loop in the thread.
  void run_thread()
  {
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    while (!stop_thread_)
    {
      lock.unlock();
      run(true);
      lock.lock();
    }
  }

  // Entry point for the select loop thread.
  static void call_run_thread(kqueue_reactor* reactor)
  {
    reactor->run_thread();
  }

  // Interrupt the select loop.
  void interrupt()
  {
    interrupter_.interrupt();
  }

  // Create the kqueue file descriptor. Throws an exception if the descriptor
  // cannot be created.
  static int do_kqueue_create()
  {
    int fd = kqueue();
    if (fd == -1)
    {
      boost::throw_exception(
          boost::system::system_error(
            boost::system::error_code(errno,
              boost::asio::error::get_system_category()),
            "kqueue"));
    }
    return fd;
  }

  // Check if all timer queues are empty.
  bool all_timer_queues_are_empty() const
  {
    for (std::size_t i = 0; i < timer_queues_.size(); ++i)
      if (!timer_queues_[i]->empty())
        return false;
    return true;
  }

  // Get the timeout value for the kevent call.
  timespec* get_timeout(timespec& ts)
  {
    if (all_timer_queues_are_empty())
      return 0;

    // By default we will wait no longer than 5 minutes. This will ensure that
    // any changes to the system clock are detected after no longer than this.
    boost::posix_time::time_duration minimum_wait_duration
      = boost::posix_time::minutes(5);

    for (std::size_t i = 0; i < timer_queues_.size(); ++i)
    {
      boost::posix_time::time_duration wait_duration
        = timer_queues_[i]->wait_duration();
      if (wait_duration < minimum_wait_duration)
        minimum_wait_duration = wait_duration;
    }

    if (minimum_wait_duration > boost::posix_time::time_duration())
    {
      ts.tv_sec = minimum_wait_duration.total_seconds();
      ts.tv_nsec = minimum_wait_duration.total_nanoseconds() % 1000000000;
    }
    else
    {
      ts.tv_sec = 0;
      ts.tv_nsec = 0;
    }

    return &ts;
  }

  // Cancel all operations associated with the given descriptor. The do_cancel
  // function of the handler objects will be invoked. This function does not
  // acquire the kqueue_reactor's mutex.
  void cancel_ops_unlocked(socket_type descriptor)
  {
    bool interrupt = read_op_queue_.cancel_operations(descriptor);
    interrupt = write_op_queue_.cancel_operations(descriptor) || interrupt;
    interrupt = except_op_queue_.cancel_operations(descriptor) || interrupt;
    if (interrupt)
      interrupter_.interrupt();
  }

  // Clean up operations and timers. We must not hold the lock since the
  // destructors may make calls back into this reactor. We make a copy of the
  // vector of timer queues since the original may be modified while the lock
  // is not held.
  void complete_operations_and_timers(
      boost::asio::detail::mutex::scoped_lock& lock)
  {
    timer_queues_for_cleanup_ = timer_queues_;
    lock.unlock();
    read_op_queue_.complete_operations();
    write_op_queue_.complete_operations();
    except_op_queue_.complete_operations();
    for (std::size_t i = 0; i < timer_queues_for_cleanup_.size(); ++i)
      timer_queues_for_cleanup_[i]->complete_timers();
  }

  // Mutex to protect access to internal data.
  boost::asio::detail::mutex mutex_;

  // The kqueue file descriptor.
  int kqueue_fd_;

  // Whether the kqueue wait call is currently in progress
  bool wait_in_progress_;

  // The interrupter is used to break a blocking kevent call.
  select_interrupter interrupter_;

  // The queue of read operations.
  reactor_op_queue<socket_type> read_op_queue_;

  // The queue of write operations.
  reactor_op_queue<socket_type> write_op_queue_;

  // The queue of except operations.
  reactor_op_queue<socket_type> except_op_queue_;

  // The timer queues.
  vostok::network::vector_size_t<timer_queue_base*> timer_queues_;

  // A copy of the timer queues, used when cleaning up timers. The copy is
  // stored as a class data member to avoid unnecessary memory allocation.
  vostok::network::vector_size_t<timer_queue_base*> timer_queues_for_cleanup_;

  // The descriptors that are pending cancellation.
  vostok::network::vector_size_t<socket_type> pending_cancellations_;

  // Does the reactor loop thread need to stop.
  bool stop_thread_;

  // The thread that is running the reactor loop.
  boost::asio::detail::thread* thread_;

  // Whether the service has been shut down.
  bool shutdown_;

  // Whether we need to call kqueue the next time the reactor is run.
  bool need_kqueue_wait_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_KQUEUE)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_KQUEUE_REACTOR_HPP
