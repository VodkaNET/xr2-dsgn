////////////////////////////////////////////////////////////////////////////
//	Created		: 06.01.2011
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_CORE_INDEX_BUFFER_INLINE_H_INCLUDED
#define VOSTOK_RENDER_CORE_INDEX_BUFFER_INLINE_H_INCLUDED

namespace vostok {
namespace render {

inline untyped_buffer& index_buffer::buffer	( ) const
{
	return		*m_buffer;
}

inline u32 index_buffer::discard_id			( ) const
{
	return		m_discard_id;
}

inline void index_buffer::flush				( )
{
	m_position	= m_size;
}

} // namespace render
} // namespace vostok

#endif // #ifndef VOSTOK_RENDER_CORE_INDEX_BUFFER_INLINE_H_INCLUDED