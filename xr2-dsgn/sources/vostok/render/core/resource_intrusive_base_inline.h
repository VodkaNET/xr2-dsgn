////////////////////////////////////////////////////////////////////////////
//	Created		: 06.01.2011
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_CORE_RESOURCE_INTRUSIVE_BASE_INLINE_H_INCLUDED
#define VOSTOK_RENDER_CORE_RESOURCE_INTRUSIVE_BASE_INLINE_H_INCLUDED

namespace vostok {
namespace render {

inline resource_intrusive_base::resource_intrusive_base	( ) :
	m_reference_count							( 0 )
{
}

template < typename T >
inline void resource_intrusive_base::destroy			( T const* const instance )
{
	instance->T::destroy_impl	( );
}

} // namespace render
} // namespace vostok

#endif // #ifndef VOSTOK_RENDER_CORE_RESOURCE_INTRUSIVE_BASE_INLINE_H_INCLUDED