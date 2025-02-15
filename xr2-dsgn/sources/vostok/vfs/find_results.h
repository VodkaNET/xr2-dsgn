////////////////////////////////////////////////////////////////////////////
//	Created		: 06.05.2011
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VFS_FIND_RESULTS_STRUCT_H_INCLUDED
#define VFS_FIND_RESULTS_STRUCT_H_INCLUDED

#include <vostok/vfs/locked_iterator.h>

namespace vostok {
namespace vfs {

typedef	boost::function< void (vfs_locked_iterator const &, result_enum) >	find_callback;

enum	find_enum					{	find_recursively	=	1 << 0,
										find_file_only		=	1 << 1, };

template class VOSTOK_VFS_API boost::function	< void (vfs_locked_iterator const &, result_enum) >;

} // namespace vfs
} // namespace vostok

#endif // #ifndef VFS_FIND_RESULTS_STRUCT_H_INCLUDED
