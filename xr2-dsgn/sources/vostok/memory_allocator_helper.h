////////////////////////////////////////////////////////////////////////////
//	Created 	: 30.09.2008
//	Author		: Dmitriy Iassenev, Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_MEMORY_ALLOCATOR_HELPER_H_INCLUDED
#define VOSTOK_MEMORY_ALLOCATOR_HELPER_H_INCLUDED

#include <boost/type_traits/is_polymorphic.hpp>
#include <vostok/memory_debug_parameters.h>
#include <typeinfo>
#include <new.h>

namespace vostok {
namespace memory {

#ifdef _MANAGED
#	pragma managed (push, on)
	template <typename A, typename T>
	inline void	free_helper			( A& alloc, T* pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
#	pragma managed( pop )
#else // #ifdef _MANAGED
	template <typename A, typename T>
	inline void	free_helper			( A& alloc, T*& pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
#endif // #ifdef _MANAGED

template <typename T>
struct new_helper
{
	template <typename A>
	static inline pvoid call		( A& alloc VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
}; // struct new_helper<T>

template <typename T>
struct new_array_helper
{
	template <typename A>
	static inline T* call			( A& alloc, u32 count VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
}; // struct new_array_helper<T>

#ifdef _MANAGED
#	pragma managed (push, on)
	template < typename A, typename T >
	void		delete_helper		( A& alloc, T const* pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
	template < typename A, typename T, typename P >
	void		delete_helper		( A& alloc, T const* pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION, P const& delete_predicate);
#	pragma managed( pop )
#else // #ifdef _MANAGED
	template < typename A, typename T >
	inline void	delete_helper		( A& alloc, T*& pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
	template < typename A, typename T, typename P >
	inline void	delete_helper		( A& alloc, T*& pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION, P const& delete_predicate);
#endif // #ifdef _MANAGED

template < typename A, typename T >
inline void		delete_array_helper	( A& alloc, T*& pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );

template < typename A, typename T, typename P >
inline void		delete_array_helper	( A& alloc, T*& pointer VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION, P const& delete_predicate);
	
template <typename A>
inline pvoid	malloc_helper		( A& alloc, size_t size, pcstr description VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
template <typename A>
inline pvoid	malloc_helper		( A& alloc, size_t size VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );

template <typename A, typename T>
inline pvoid	realloc_helper		( A& alloc, T* pointer, size_t size, pcstr description VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );
template <typename A, typename T>
inline pvoid	realloc_helper		( A& alloc, T* pointer, size_t size VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION );

template <typename T>
inline T&		strip_pointer		( T* const t ) { return *t; }

template <typename T>
inline T&		strip_pointer		( T& t ) { return t; }

} // namespace memory
} // namespace vostok

#include <vostok/memory_allocator_helper_inline.h>

#endif // #ifndef VOSTOK_MEMORY_allocator_helper_H_INCLUDED
