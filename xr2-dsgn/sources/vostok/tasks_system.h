////////////////////////////////////////////////////////////////////////////
//	Created		: 06.11.2009
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_TASKS_MANAGER_H_INCLUDED
#define VOSTOK_TASKS_MANAGER_H_INCLUDED

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace vostok {
namespace tasks {

typedef			boost::function< void () >		task_function;

enum			task_type_flags_enum	{ task_type_flags_no_self_parallelization_hint	=	1 << 0, };

class			task;
class			task_type;

enum			execute_while_wait_for_children_enum	{	execute_while_wait_for_children_false, 
															execute_while_wait_for_children_true	};

enum			do_logging_bool							{	do_logging_false, do_logging_true	};

VOSTOK_CORE_API	void   			initialize				(u32 max_task_threads, 
										 				 u32 max_non_task_threads,
										 				 u32 min_permanent_working_threads,
										 				 execute_while_wait_for_children_enum,
														 do_logging_bool);

VOSTOK_CORE_API	void   			finalize				();

VOSTOK_CORE_API	void   			register_current_thread_as_core_user	();

VOSTOK_CORE_API	task_type *		create_new_task_type	(pcstr description, enum_flags<task_type_flags_enum> flags);

VOSTOK_CORE_API	void			spawn_task				(task_function const &	function, 
										 				 task_type *			type, 
										 				 task *					parent = NULL);
VOSTOK_CORE_API	task *			grab_next_task			();
VOSTOK_CORE_API	void			wait_for_all_children	();
VOSTOK_CORE_API	void			wait_for_task_list		(task * task_list);

VOSTOK_CORE_API	void			pause_all_task_threads	();
VOSTOK_CORE_API	void			resume_all_task_threads	();

VOSTOK_CORE_API	bool			zero_tasks				(); // remove this func from interface
VOSTOK_CORE_API	void			check_all_free			(); // remove this func from interface
VOSTOK_CORE_API	void			collect_garbage			(u32 * out_tasks_freed_count = NULL); // remove this func from interface

VOSTOK_CORE_API	void			set_logging				(do_logging_bool do_logging);

} // namespace tasks
} // namespace vostok

#endif // #ifndef TASKS_MANAGER_H_INCLUDED