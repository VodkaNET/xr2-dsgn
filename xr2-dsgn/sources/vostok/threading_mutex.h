////////////////////////////////////////////////////////////////////////////
//	Created 	: 25.09.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_THREADING_MUTEX_H_INCLUDED
#define VOSTOK_THREADING_MUTEX_H_INCLUDED

#include <boost/noncopyable.hpp>
#include <vostok/threading_policies.h>

namespace vostok {
namespace threading {

template < typename MutexType >
class mutex_raii_impl : private boost::noncopyable {
public:
	inline				mutex_raii_impl	( MutexType const& lock ) : m_lock( lock )	{ m_lock.lock(); m_locked = true; }
	inline	void		clear			( )											{ if ( m_locked ) { m_lock.unlock(); m_locked = false; } }
	inline				~mutex_raii_impl( )											{ clear(); }
private:
	MutexType const&	m_lock;
	bool				m_locked;
}; // class mutex_raii

class VOSTOK_CORE_API mutex_tasks_unaware : private core::noncopyable {
public:
				mutex_tasks_unaware	( );
				~mutex_tasks_unaware( );
				void	lock		( ) const;
				void	unlock		( ) const;
				bool	try_lock	( ) const;
public:
	typedef mutex_raii_impl< mutex_tasks_unaware >	mutex_raii;

private:
#if VOSTOK_PLATFORM_WINDOWS_32
	mutable u64			m_mutex[3]; // sizeof(CRITICAL_SECTION);
#elif VOSTOK_PLATFORM_WINDOWS_64 // #if VOSTOK_PLATFORM_WINDOWS_32
	mutable u64			m_mutex[5]; // sizeof(CRITICAL_SECTION);
#elif VOSTOK_PLATFORM_XBOX_360 // #elif VOSTOK_PLATFORM_WINDOWS_64
	mutable u64			m_mutex[4]; // sizeof(CRITICAL_SECTION);
#elif VOSTOK_PLATFORM_PS3 // #elif VOSTOK_PLATFORM_XBOX_360
	mutable u64			m_mutex[3]; // sizeof(sys_lwmutex_t);
#endif // #elif VOSTOK_PLATFORM_XBOX_360
}; // class mutex_tasks_unaware

class VOSTOK_CORE_API mutex : private core::noncopyable {
public:
	inline				mutex		( ) { }
				void	lock		( ) const;
				void	unlock		( ) const;
				bool	try_lock	( ) const;

public:
	typedef mutex_raii_impl< mutex >	mutex_raii;

private:
	mutex_tasks_unaware	m_mutex;
};

typedef	mutex_tasks_unaware::mutex_raii	mutex_tasks_unaware_raii;
typedef	mutex::mutex_raii				mutex_raii;

} // namespace threading
} // namespace vostok

#endif // #ifndef VOSTOK_THREADING_MUTEX_H_INCLUDED