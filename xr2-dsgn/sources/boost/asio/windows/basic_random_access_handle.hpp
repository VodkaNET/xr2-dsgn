//
// basic_random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_BASIC_RANDOM_ACCESS_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_BASIC_RANDOM_ACCESS_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <cstddef>
#include <boost/config.hpp>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/error.hpp>
#include <boost/asio/windows/basic_handle.hpp>
#include <boost/asio/windows/random_access_handle_service.hpp>
#include <boost/asio/detail/throw_error.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace windows {

/// Provides random-access handle functionality.
/**
 * The windows::basic_random_access_handle class template provides asynchronous
 * and blocking random-access handle functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename RandomAccessHandleService = random_access_handle_service>
class basic_random_access_handle
  : public basic_handle<RandomAccessHandleService>
{
public:
  /// The native representation of a handle.
  typedef typename RandomAccessHandleService::native_type native_type;

  /// Construct a basic_random_access_handle without opening it.
  /**
   * This constructor creates a random-access handle without opening it. The
   * handle needs to be opened before data can be written to or or read from it.
   *
   * @param io_service The io_service object that the random-access handle will
   * use to dispatch handlers for any asynchronous operations performed on the
   * handle.
   */
  explicit basic_random_access_handle(boost::asio::io_service& io_service)
    : basic_handle<RandomAccessHandleService>(io_service)
  {
  }

  /// Construct a basic_random_access_handle on an existing native handle.
  /**
   * This constructor creates a random-access handle object to hold an existing
   * native handle.
   *
   * @param io_service The io_service object that the random-access handle will
   * use to dispatch handlers for any asynchronous operations performed on the
   * handle.
   *
   * @param native_handle The new underlying handle implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_random_access_handle(boost::asio::io_service& io_service,
      const native_type& native_handle)
    : basic_handle<RandomAccessHandleService>(io_service, native_handle)
  {
  }

  /// Write some data to the handle at the specified offset.
  /**
   * This function is used to write data to the random-access handle. The
   * function call will block until one or more bytes of the data has been
   * written successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The write_some_at operation may not write all of the data. Consider
   * using the @ref write_at function if you need to ensure that all data is
   * written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.write_some_at(42, boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some_at(boost::uint64_t offset,
      const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.write_some_at(
        this->implementation, offset, buffers, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Write some data to the handle at the specified offset.
  /**
   * This function is used to write data to the random-access handle. The
   * function call will block until one or more bytes of the data has been
   * written successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write_at function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some_at(boost::uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return this->service.write_some_at(
        this->implementation, offset, buffers, ec);
  }

  /// Start an asynchronous write at the specified offset.
  /**
   * This function is used to asynchronously write data to the random-access
   * handle. The function call always returns immediately.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the write operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * boost::asio::io_service::post().
   *
   * @note The write operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write_at function if you need to ensure that
   * all data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_write_some_at(42, boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some_at(boost::uint64_t offset,
      const ConstBufferSequence& buffers, WriteHandler handler)
  {
    this->service.async_write_some_at(
        this->implementation, offset, buffers, handler);
  }

  /// Read some data from the handle at the specified offset.
  /**
   * This function is used to read data from the random-access handle. The
   * function call will block until one or more bytes of data has been read
   * successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read_at function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.read_some_at(42, boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some_at(boost::uint64_t offset,
      const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.read_some_at(
        this->implementation, offset, buffers, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Read some data from the handle at the specified offset.
  /**
   * This function is used to read data from the random-access handle. The
   * function call will block until one or more bytes of data has been read
   * successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read_at function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some_at(boost::uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return this->service.read_some_at(
        this->implementation, offset, buffers, ec);
  }

  /// Start an asynchronous read at the specified offset.
  /**
   * This function is used to asynchronously read data from the random-access
   * handle. The function call always returns immediately.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the read operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * boost::asio::io_service::post().
   *
   * @note The read operation may not read all of the requested number of bytes.
   * Consider using the @ref async_read_at function if you need to ensure that
   * the requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_read_some_at(42, boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  void async_read_some_at(boost::uint64_t offset,
      const MutableBufferSequence& buffers, ReadHandler handler)
  {
    this->service.async_read_some_at(
        this->implementation, offset, buffers, handler);
  }
};

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_WINDOWS_BASIC_RANDOM_ACCESS_HANDLE_HPP
