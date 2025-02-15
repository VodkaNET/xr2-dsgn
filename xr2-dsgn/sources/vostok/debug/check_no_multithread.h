////////////////////////////////////////////////////////////////////////////
//	Created 	: 06.10.2009
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////
#ifndef VOSTOK_DEBUG_CHECK_NO_MULTITHREAD
#define VOSTOK_DEBUG_CHECK_NO_MULTITHREAD

// instructions:
// inherit from class no_multithread
// put VOSTOK_CHECK_NO_MULTITHREAD in class functions

#ifdef MASTER_GOLD
#	define VOSTOK_CHECK_NO_MULTITHREAD
#else // #ifdef MASTER_GOLD
#	define VOSTOK_CHECK_NO_MULTITHREAD	vostok::debug::detail::check_no_multithread_raii	\
																check_no_multithread_raii$(this)
#endif // #ifdef MASTER_GOLD

namespace vostok {
namespace debug {
namespace detail {
class check_no_multithread_raii;
} // namespace detail
} // namespace debug

class no_multithread
{
public:
			no_multithread	();

private:
	void 	on_function_start	() const;
	void 	on_function_end		() const;

	friend	class				debug::detail::check_no_multithread_raii;

private:
	mutable threading::atomic32_type	m_current_user_thread_id;
	mutable threading::atomic32_type	m_current_num_uses;
};

extern command_line::key		g_dont_check_multithreaded_safety;

} // namespace vostok

#include <vostok/debug/check_no_multithread_inline.h>

#endif // #ifndef VOSTOK_DEBUG_CHECK_NO_MULTITHREAD