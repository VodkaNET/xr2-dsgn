//
// basic_stream_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAM_SOCKET_HPP
#define BOOST_ASIO_BASIC_STREAM_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <cstddef>
#include <boost/config.hpp>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/basic_socket.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/stream_socket_service.hpp>
#include <boost/asio/detail/throw_error.hpp>

namespace boost {
namespace asio {

/// Provides stream-oriented socket functionality.
/**
 * The basic_stream_socket class template provides asynchronous and blocking
 * stream-oriented socket functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Protocol,
    typename StreamSocketService = stream_socket_service<Protocol> >
class basic_stream_socket
  : public basic_socket<Protocol, StreamSocketService>
{
public:
  /// The native representation of a socket.
  typedef typename StreamSocketService::native_type native_type;

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  /// Construct a basic_stream_socket without opening it.
  /**
   * This constructor creates a stream socket without opening it. The socket
   * needs to be opened and then connected or accepted before data can be sent
   * or received on it.
   *
   * @param io_service The io_service object that the stream socket will use to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_stream_socket(boost::asio::io_service& io_service)
    : basic_socket<Protocol, StreamSocketService>(io_service)
  {
  }

  /// Construct and open a basic_stream_socket.
  /**
   * This constructor creates and opens a stream socket. The socket needs to be
   * connected or accepted before data can be sent or received on it.
   *
   * @param io_service The io_service object that the stream socket will use to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_socket(boost::asio::io_service& io_service,
      const protocol_type& protocol)
    : basic_socket<Protocol, StreamSocketService>(io_service, protocol)
  {
  }

  /// Construct a basic_stream_socket, opening it and binding it to the given
  /// local endpoint.
  /**
   * This constructor creates a stream socket and automatically opens it bound
   * to the specified endpoint on the local machine. The protocol used is the
   * protocol associated with the given endpoint.
   *
   * @param io_service The io_service object that the stream socket will use to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the stream
   * socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_socket(boost::asio::io_service& io_service,
      const endpoint_type& endpoint)
    : basic_socket<Protocol, StreamSocketService>(io_service, endpoint)
  {
  }

  /// Construct a basic_stream_socket on an existing native socket.
  /**
   * This constructor creates a stream socket object to hold an existing native
   * socket.
   *
   * @param io_service The io_service object that the stream socket will use to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket The new underlying socket implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_socket(boost::asio::io_service& io_service,
      const protocol_type& protocol, const native_type& native_socket)
    : basic_socket<Protocol, StreamSocketService>(
        io_service, protocol, native_socket)
  {
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the stream socket. The function
   * call will block until one or more bytes of the data has been sent
   * successfully, or an until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.send(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.send(
        this->implementation, buffers, 0, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the stream socket. The function
   * call will block until one or more bytes of the data has been sent
   * successfully, or an until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.send(boost::asio::buffer(data, size), 0);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.send(
        this->implementation, buffers, flags, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the stream socket. The function
   * call will block until one or more bytes of the data has been sent
   * successfully, or an until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent. Returns 0 if an error occurred.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->service.send(this->implementation, buffers, flags, ec);
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send data on the stream socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * boost::asio::io_service::post().
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_send(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  void async_send(const ConstBufferSequence& buffers, WriteHandler handler)
  {
    this->service.async_send(this->implementation, buffers, 0, handler);
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send data on the stream socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * boost::asio::io_service::post().
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_send(boost::asio::buffer(data, size), 0, handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  void async_send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, WriteHandler handler)
  {
    this->service.async_send(this->implementation, buffers, flags, handler);
  }

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the stream socket. The function
   * call will block until one or more bytes of data has been received
   * successfully, or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.receive(this->implementation, buffers, 0, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the stream socket. The function
   * call will block until one or more bytes of data has been received
   * successfully, or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size), 0);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.receive(
        this->implementation, buffers, flags, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the stream socket. The function
   * call will block until one or more bytes of data has been received
   * successfully, or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received. Returns 0 if an error occurred.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->service.receive(this->implementation, buffers, flags, ec);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the stream
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * boost::asio::io_service::post().
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref async_read function if you need to ensure
   * that the requested amount of data is received before the asynchronous
   * operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  void async_receive(const MutableBufferSequence& buffers, ReadHandler handler)
  {
    this->service.async_receive(this->implementation, buffers, 0, handler);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the stream
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param flags Flags specifying how the receive call is to be made.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. Invocation
   * of the handler will be performed in a manner equivalent to using
   * boost::asio::io_service::post().
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref async_read function if you need to ensure
   * that the requested amount of data is received before the asynchronous
   * operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(boost::asio::buffer(data, size), 0, handler);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  void async_receive(const MutableBufferSequence& buffers,
      socket_base::message_flags flags, ReadHandler handler)
  {
    this->service.async_receive(this->implementation, buffers, flags, handler);
  }

  /// Write some data to the socket.
  /**
   * This function is used to write data to the stream socket. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the socket.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.write_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.send(this->implementation, buffers, 0, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Write some data to the socket.
  /**
   * This function is used to write data to the stream socket. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the socket.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->service.send(this->implementation, buffers, 0, ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write data to the stream socket.
   * The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be written to the socket.
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
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_write_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some(const ConstBufferSequence& buffers,
      WriteHandler handler)
  {
    this->service.async_send(this->implementation, buffers, 0, handler);
  }

  /// Read some data from the socket.
  /**
   * This function is used to read data from the stream socket. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
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
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.read_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->service.receive(this->implementation, buffers, 0, ec);
    boost::asio::detail::throw_error(ec);
    return s;
  }

  /// Read some data from the socket.
  /**
   * This function is used to read data from the stream socket. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->service.receive(this->implementation, buffers, 0, ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read data from the stream socket.
   * The function call always returns immediately.
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
   * Consider using the @ref async_read function if you need to ensure that the
   * requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_read_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * vostok::network::vector.
   */
  template <typename MutableBufferSequence, typename ReadHandler>
  void async_read_some(const MutableBufferSequence& buffers,
      ReadHandler handler)
  {
    this->service.async_receive(this->implementation, buffers, 0, handler);
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_STREAM_SOCKET_HPP
