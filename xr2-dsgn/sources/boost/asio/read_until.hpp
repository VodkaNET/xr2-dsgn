//
// read_until.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_READ_UNTIL_HPP
#define BOOST_ASIO_READ_UNTIL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <cstddef>
#include <boost/config.hpp>
#include <boost/regex.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/detail/workaround.hpp>
#include <string>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/basic_streambuf.hpp>
#include <boost/asio/error.hpp>

namespace boost {
namespace asio {

namespace detail
{
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x610))
  template <typename T>
  struct has_result_type
  {
    template <typename U> struct inner
    {
        struct big { char a[100]; };
        static big helper(U, ...);
        static char helper(U, typename U::result_type* = 0);
    };
    static const T& ref();
    enum { value = (sizeof((inner<const T&>::helper)((ref)())) == 1) };
  };
#else // BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x610))
  template <typename T>
  struct has_result_type
  {
    struct big { char a[100]; };
    template <typename U> static big helper(U, ...);
    template <typename U> static char helper(U, typename U::result_type* = 0);
    static const T& ref();
    enum { value = (sizeof((helper)((ref)())) == 1) };
  };
#endif // BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x610))
} // namespace detail

/// Type trait used to determine whether a type can be used as a match condition
/// function with read_until and async_read_until.
template <typename T>
struct is_match_condition
{
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true if the type may be used as a match condition.
  static const bool value;
#else
  enum
  {
    value = boost::is_function<typename boost::remove_pointer<T>::type>::value
      || detail::has_result_type<T>::value
  };
#endif
};

/**
 * @defgroup read_until boost::asio::read_until
 *
 * @brief Read data into a streambuf until it contains a delimiter, matches a
 * regular expression, or a function object indicates a match.
 */
/*@{*/

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 *
 * @par Example
 * To read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * boost::asio::read_until(s, b, '\n');
 * std::istream is(&b);
 * vostok::network::std_string line;
 * std::getline(is, line); @endcode
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim);

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim,
    boost::system::error_code& ec);

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 *
 * @par Example
 * To read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * boost::asio::read_until(s, b, "\r\n");
 * std::istream is(&b);
 * vostok::network::std_string line;
 * std::getline(is, line); @endcode
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const vostok::network::std_string& delim);

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const vostok::network::std_string& delim,
    boost::system::error_code& ec);

/// Read data into a streambuf until some part of the data it contains matches
/// a regular expression.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains some data that matches a regular expression.
 * The call will block until one of the following conditions is true:
 *
 * @li A substring of the streambuf's get area matches the regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains data that
 * matches the regular expression, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the substring that matches the regular expression.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the regular expression. An
 * application will typically leave that data in the streambuf for a subsequent
 * read_until operation to examine.
 *
 * @par Example
 * To read data into a streambuf until a CR-LF sequence is encountered:
 * @code boost::asio::streambuf b;
 * boost::asio::read_until(s, b, boost::regex("\r\n"));
 * std::istream is(&b);
 * vostok::network::std_string line;
 * std::getline(is, line); @endcode
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr);

/// Read data into a streambuf until some part of the data it contains matches
/// a regular expression.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains some data that matches a regular expression.
 * The call will block until one of the following conditions is true:
 *
 * @li A substring of the streambuf's get area matches the regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains data that
 * matches the regular expression, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the substring that matches the regular expression. Returns 0 if an error
 * occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the regular expression. An
 * application will typically leave that data in the streambuf for a subsequent
 * read_until operation to examine.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    boost::system::error_code& ec);

/// Read data into a streambuf until a function object indicates a match.
/**
 * This function is used to read data into the specified streambuf until a
 * user-defined match condition function object, when applied to the data
 * contained in the streambuf, indicates a successful match. The call will
 * block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<basic_streambuf<Allocator>::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @returns The number of bytes in the streambuf's get area that have been fully
 * consumed by the match function.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the function object. An application
 * will typically leave that data in the streambuf for a subsequent
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To read data into a streambuf until whitespace is encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::streambuf::const_buffers_type> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * boost::asio::streambuf b;
 * boost::asio::read_until(s, b, match_whitespace);
 * @endcode
 *
 * To read data into a streambuf until a matching character is found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * boost::asio::streambuf b;
 * boost::asio::read_until(s, b, match_char('a'));
 * @endcode
 */
template <typename SyncReadStream, typename Allocator, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, MatchCondition match_condition,
    typename boost::enable_if<is_match_condition<MatchCondition> >::type* = 0);

/// Read data into a streambuf until a function object indicates a match.
/**
 * This function is used to read data into the specified streambuf until a
 * user-defined match condition function object, when applied to the data
 * contained in the streambuf, indicates a successful match. The call will
 * block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<basic_streambuf<Allocator>::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area that have been fully
 * consumed by the match function. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the function object. An application
 * will typically leave that data in the streambuf for a subsequent
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 */
template <typename SyncReadStream, typename Allocator, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename boost::enable_if<is_match_condition<MatchCondition> >::type* = 0);

/*@}*/
/**
 * @defgroup async_read_until boost::asio::async_read_until
 *
 * @brief Start an asynchronous operation to read data into a streambuf until it
 * contains a delimiter, matches a regular expression, or a function object
 * indicates a match.
 */
/*@{*/

/// Start an asynchronous operation to read data into a streambuf until it
/// contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains the specified delimiter.
 * The function call always returns immediately. The asynchronous operation
 * will continue until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function. If the streambuf's get area already contains the
 * delimiter, the asynchronous operation completes immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read. Ownership of
 * the streambuf is retained by the caller, which must guarantee that it remains
 * valid until the handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area up to and including the delimiter.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation of
 * the handler will be performed in a manner equivalent to using
 * boost::asio::io_service::post().
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond the delimiter. An application will typically
 * leave that data in the streambuf for a subsequent async_read_until operation
 * to examine.
 *
 * @par Example
 * To asynchronously read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::istream is(&b);
 *     vostok::network::std_string line;
 *     std::getline(is, line);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, b, '\n', handler); @endcode
 */
template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
void async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    char delim, ReadHandler handler);

/// Start an asynchronous operation to read data into a streambuf until it
/// contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains the specified delimiter.
 * The function call always returns immediately. The asynchronous operation
 * will continue until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function. If the streambuf's get area already contains the
 * delimiter, the asynchronous operation completes immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read. Ownership of
 * the streambuf is retained by the caller, which must guarantee that it remains
 * valid until the handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area up to and including the delimiter.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation of
 * the handler will be performed in a manner equivalent to using
 * boost::asio::io_service::post().
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond the delimiter. An application will typically
 * leave that data in the streambuf for a subsequent async_read_until operation
 * to examine.
 *
 * @par Example
 * To asynchronously read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::istream is(&b);
 *     vostok::network::std_string line;
 *     std::getline(is, line);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, b, "\r\n", handler); @endcode
 */
template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
void async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const vostok::network::std_string& delim,
    ReadHandler handler);

/// Start an asynchronous operation to read data into a streambuf until some
/// part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains some data that matches a
 * regular expression. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li A substring of the streambuf's get area matches the regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function. If the streambuf's get area already contains data
 * that matches the regular expression, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read. Ownership of
 * the streambuf is retained by the caller, which must guarantee that it remains
 * valid until the handler is called.
 *
 * @param expr The regular expression.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area up to and including the substring
 *   // that matches the regular. expression.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation of
 * the handler will be performed in a manner equivalent to using
 * boost::asio::io_service::post().
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond that which matched the regular expression. An
 * application will typically leave that data in the streambuf for a subsequent
 * async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a streambuf until a CR-LF sequence is
 * encountered:
 * @code boost::asio::streambuf b;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::istream is(&b);
 *     vostok::network::std_string line;
 *     std::getline(is, line);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, b, boost::regex("\r\n"), handler); @endcode
 */
template <typename AsyncReadStream, typename Allocator, typename ReadHandler>
void async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    ReadHandler handler);

/// Start an asynchronous operation to read data into a streambuf until a
/// function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until a user-defined match condition function object, when applied
 * to the data contained in the streambuf, indicates a successful match. The
 * function call always returns immediately. The asynchronous operation will
 * continue until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function. If the match condition function object already
 * indicates a match, the operation completes immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<basic_streambuf<Allocator>::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area that have been fully consumed by the
 *   // match function. O if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation of
 * the handler will be performed in a manner equivalent to using
 * boost::asio::io_service::post().
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond that which matched the function object. An
 * application will typically leave that data in the streambuf for a subsequent
 * async_read_until operation to examine.
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To asynchronously read data into a streambuf until whitespace is encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::streambuf::const_buffers_type> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * boost::asio::streambuf b;
 * boost::asio::async_read_until(s, b, match_whitespace, handler);
 * @endcode
 *
 * To asynchronously read data into a streambuf until a matching character is
 * found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * boost::asio::streambuf b;
 * boost::asio::async_read_until(s, b, match_char('a'), handler);
 * @endcode
 */
template <typename AsyncReadStream, typename Allocator,
    typename MatchCondition, typename ReadHandler>
void async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition, ReadHandler handler,
    typename boost::enable_if<is_match_condition<MatchCondition> >::type* = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/impl/read_until.ipp>

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_READ_UNTIL_HPP
