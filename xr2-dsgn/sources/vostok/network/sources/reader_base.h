////////////////////////////////////////////////////////////////////////////
//	Created		: 29.03.2010
//	Author		: Alexander Maniluk
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef READER_BASE_H_INCLUDED
#define READER_BASE_H_INCLUDED

#include <vostok/debug/signalling_bool.h>

namespace vostok
{

template <typename Reader, typename Device>
class seekable_reader
{
public:
	typedef	typename Device::size_type			size_type;

	signalling_bool	advance		( size_type const offset );
	signalling_bool	seek		( size_type const new_position );
	signalling_bool	rewind		( );

	bool			eof			( ) const;
	size_type		elapsed		( ) const;
	size_type		tell		( ) const;
	size_type		length		( ) const;
}; // class seekable_reader

template <typename SeekableReader>
class strict_seekable_reader
{
public:
	typedef	typename SeekableReader::size_type	size_type;

	void			advance		( size_type const offset );
	void			seek		( size_type const new_position );
	void			rewind		( );

	bool			eof			( ) const;
	size_type		elapsed		( ) const;
	size_type		tell		( ) const;
	size_type		length		( ) const;
}; // class strict_seekable_reader


template <typename Reader, typename Device>
class direct_accessible_reader
{
public:
	typedef typename Device::const_pointer_type	const_pointer_type;

	const_pointer_type	pointer		( ) const;
	const_pointer_type	data		( ) const;
}; // class direct_accessible_reader

} // namespace vostok

#include "reader_base_inline.h"

#endif // #ifndef READER_BASE_H_INCLUDED