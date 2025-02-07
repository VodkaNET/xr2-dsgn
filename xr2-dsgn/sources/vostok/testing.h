////////////////////////////////////////////////////////////////////////////
//	Created		: 15.06.2009
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_CORE_TESTING_H_INCLUDED
#define VOSTOK_CORE_TESTING_H_INCLUDED

#include <vostok/intrusive_list.h>

namespace vostok {
namespace testing {

VOSTOK_CORE_API void  initialize				( core::engine * engine );
VOSTOK_CORE_API void  finalize				( );
VOSTOK_CORE_API u32   tests_failed_so_far		( );
VOSTOK_CORE_API bool	run_tests_command_line	( );
VOSTOK_CORE_API bool	is_testing				();
VOSTOK_CORE_API void	on_exception			(assert_enum			assert_type, 
											 pcstr					description, 
											 _EXCEPTION_POINTERS*	exception_information,
											 bool					is_assertion);

extern command_line::key	g_run_tests;
extern command_line::key	g_run_tests_and_exit;

class VOSTOK_CORE_API test_base
{
public:
							test_base	() :	m_next_test(NULL) {}
	virtual					~test_base	() {}
	virtual	void			test		()	=	0;
public:
	test_base*				m_next_test;
};

template <class derived>
class suite_base
{
public:
							suite_base	();
	static 	bool			run_tests	();
	static 	void			add_test	(test_base* const test);
	static 	derived*		singleton	();

private:
	typedef	intrusive_list<test_base, test_base *, &test_base::m_next_test, threading::mutex_tasks_unaware>	tests;
	tests					m_tests;
	static	derived*		s_suite;
	static	threading::atomic32_type	s_suite_creation_flag;
	class	memory_helper;
};

} // namespace testing

template class VOSTOK_CORE_API intrusive_list<testing::test_base, testing::test_base *, &testing::test_base::m_next_test, threading::mutex_tasks_unaware>;

} // namespace vostok

#define DEFINE_SUITE_HELPERS	public: template <class test_func>	void test (test_func*) { UNREACHABLE_CODE(); }

#define REGISTER_TEST_CLASS(test_class, suite_class)									\
	static	vostok::testing::test_class_helper<test_class, suite_class>					\
			s_test_class_helper ## test_class ## suite_class(#test_class, #suite_class);

#define DEFINE_TEST(test_name, suite_class)												\
	class test_name {};																	\
	static	vostok::testing::test_func_helper<test_name, suite_class>						\
			s_test_func_helper ## test_name ## suite_class(#test_name, #suite_class);	\
	template <>																			\
	void   suite_class::test<test_name> (test_name*)

#include <vostok/testing_inline.h>

#endif // #ifndef VOSTOK_CORE_TESTING_H_INCLUDED