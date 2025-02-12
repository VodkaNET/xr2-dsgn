////////////////////////////////////////////////////////////////////////////
//	Created 	: 16.07.2010
//	Author		: Sergey Pryshchepa
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef EDITOR_INTRUSIVE_BASE_INLINE_H_INCLUDED
#define EDITOR_INTRUSIVE_BASE_INLINE_H_INCLUDED

inline vostok::editor_base::editor_intrusive_base::editor_intrusive_base	( ) :
m_reference_count	( 0 )
{
}

template <typename T>
inline void vostok::editor_base::editor_intrusive_base::destroy			( T* object ) const
{
	CRT_DELETE			( object );
	//VOSTOK_DELETE_IMPL	( *::vostok::editor_base::g_allocator, object );
}

#endif // #ifndef EDITOR_INTRUSIVE_BASE_INLINE_H_INCLUDED