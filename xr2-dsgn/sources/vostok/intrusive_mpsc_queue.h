////////////////////////////////////////////////////////////////////////////
//	Created		: 14.12.2009
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef INTRUSIVE_MPSC_QUEUE_H_INCLUDED
#define INTRUSIVE_MPSC_QUEUE_H_INCLUDED

namespace vostok {

template < typename T, typename BaseWithMember, T* BaseWithMember::*MemberNext >
class VOSTOK_CORE_API intrusive_mpsc_queue {
public:
	typedef T			value_type;
	typedef value_type*	pointer_type;

public:
	inline			intrusive_mpsc_queue	( );
	inline			~intrusive_mpsc_queue	( );

	inline	void	push_back				( T* const value );
	inline	T*		pop_front				( T*& item_to_delete );
	inline	bool	empty					( ) const;

	inline	void	set_pop_thread_id		( );

	inline	void	push_null_node			( T* const null_node );
	inline	T*		pop_null_node			( );

	inline	bool	initialized				( ) const { return m_head != NULL; }

	inline	threading::atomic32_type	pop_thread_id	( ) const { return m_pop_thread_id; }

private:
	T*							m_head;
	threading::atomic32_type	m_pop_thread_id;
	char						m_cache_line_pad[VOSTOK_MAX_CACHE_LINE_SIZE - 1*sizeof(T*) -2*sizeof(threading::atomic32_type)];
	T*							m_tail;
}; // class intrusive_mpsc_queue

} // namespace vostok

#include <vostok/intrusive_mpsc_queue_inline.h>

#endif // #ifndef INTRUSIVE_MPSC_QUEUE_H_INCLUDED