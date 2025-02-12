////////////////////////////////////////////////////////////////////////////
//	Created		: 08.04.2011
//	Author		: 
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VFS_FREE_NODE_H_INCLUDED
#define VFS_FREE_NODE_H_INCLUDED

#include "nodes.h"
#include <vostok/vfs/hashset.h>

namespace vostok {
namespace vfs {

void   free_node						(virtual_file_system & 		file_system,
										 base_node<> *				node, 
										 base_node<> * &			root_write_lock,
										 u32						hash,
										 memory::base_allocator *	allocator);

} // namespace vfs
} // namespace vostok

#endif // #ifndef VFS_FREE_NODE_H_INCLUDED