////////////////////////////////////////////////////////////////////////////
//	Created		: 26.04.2011
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VFS_ARCHIVE_INLINE_FILE_NODE_H_INCLUDED
#define VFS_ARCHIVE_INLINE_FILE_NODE_H_INCLUDED

#include "archive_file_node_base.h"
#include "archive_inline_file_node_base.h"

namespace vostok {
namespace vfs {

#pragma pack(push, 8)

template <platform_pointer_enum T = platform_pointer_default>
class archive_inline_file_node : public archive_file_node_base<T>,
								 public archive_inline_file_node_base<T>
{
public:
	enum { flags =	vfs_node_is_archive | vfs_node_is_inlined };

public:
	archive_inline_file_node() : base(flags) {}

	void								reverse_bytes	()
	{
		((archive_file_node_base<T> *)this)->reverse_bytes();
		((archive_inline_file_node_base<T> *)this)->reverse_bytes();
		base.reverse_bytes					();
	}

public:
	base_node<T>						base;

}; // class fat_db_inline_file_node

#pragma pack(pop)

template <platform_pointer_enum T>
base_node<T> const *		cast_node	(archive_inline_file_node<T> const * node) { return & node->base; }

template <platform_pointer_enum T>
base_node<T> *				cast_node	(archive_inline_file_node<T> * node) { return & node->base; }

template <platform_pointer_enum T>
archive_inline_file_node<T> *   cast_archive_inline_file (base_node<T> * node)
{
	R_ASSERT								(!node->is_link());

	if ( node->is_folder() || !node->is_archive() || node->is_compressed() || !node->is_inlined() )
		return								NULL;

	return									cast_base_node_to< archive_inline_file_node<T> >(node);
}

template <platform_pointer_enum T>
archive_inline_file_node<T> const *   cast_archive_inline_file (base_node<T> const * node)
{
	return									node_cast<archive_inline_file_node>(const_cast<base_node<T> *>(node));
}

} // namespace vfs
} // namespace vostok

#endif // #ifndef VFS_ARCHIVE_INLINE_FILE_NODE_H_INCLUDED