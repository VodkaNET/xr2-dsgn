////////////////////////////////////////////////////////////////////////////
//	Created		: 06.05.2010
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "fs_nodes.h"
#include "fs_impl_saving_info_tree.h"
#include "fs_impl.h"
#include "fs_helper.h"
#include "fs_macros.h"
#include "resources_manager.h"
#include <vostok/fs_utils.h>

namespace vostok {
namespace fs   {

//-----------------------------------------------------------------------------------
// fat_folder_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
typename fat_folder_node<pointer_for_fat_size>::node_type *   fat_folder_node<pointer_for_fat_size>::get_first_child (bool skip_erased)
{
	if ( !skip_erased )
		return						m_first_child; 

	node_type * out_node		=	m_first_child;
	while ( out_node && is_erased_node(out_node) )
		out_node				=	out_node->m_next;

	return							out_node; 
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_folder_node<pointer_for_fat_size>::transfer_children (fat_folder_node* dest, bool no_duplicate_names)
{
	fat_node<pointer_for_fat_size>* child			=	m_first_child;
	while ( child )
	{
		fat_node<pointer_for_fat_size>* next_child	=	child->get_next();
		bool const dest_has_child	=	(dest->find_child(child->m_name) != NULL);
		if ( !no_duplicate_names || !dest_has_child )
		{
			unlink_child			(child, true);
			if ( !dest_has_child )
				dest->prepend_child	(child);
		}
		child					=	next_child;
	}
}

template <platform_pointer_enum pointer_for_fat_size>
fat_node<pointer_for_fat_size>*   fat_folder_node<pointer_for_fat_size>::find_child (const char* name)
{
	fat_node<pointer_for_fat_size> * child	=	m_first_child;
	while ( child )
	{
		ASSERT						(child->m_name);
		if ( strings::equal(child->m_name, name) )
			return					child;

		child					=	child->m_next;
	}

	return NULL;
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_folder_node<pointer_for_fat_size>::find_child (fat_node<pointer_for_fat_size> const * seeking_child) const
{
	fat_node<pointer_for_fat_size> * child	=	m_first_child;
	while ( child )
	{
		if ( child	==	seeking_child )
			return					true;

		child					=	child->m_next;
	}

	return false;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_folder_node<pointer_for_fat_size>::unlink_child (fat_node<pointer_for_fat_size> * child, bool zero_childs_parent)
{
	ASSERT(child->m_parent == cast_node());

	if ( zero_childs_parent )
		child->m_parent			=	NULL;
	
	if ( child->m_next )
		child->m_next->m_prev	=	child->m_prev;

	if ( child->m_prev )
		child->m_prev->m_next	=	child->m_next;
	else if ( m_first_child == child )
		m_first_child			=	child->m_next;

	child->m_next				=	NULL;
	child->m_prev				=	NULL;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_folder_node<pointer_for_fat_size>::prepend_child (fat_node<pointer_for_fat_size> * child)
{
	ASSERT							(!find_child(child));
	child->m_parent				=	cast_node();
	child->m_next				=	m_first_child;
	child->m_prev				=	NULL;

	if ( m_first_child )
		m_first_child->m_prev	=	child;

	m_first_child				=	child;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_folder_node<pointer_for_fat_size>::swap_child_with_next_child (node_type * current)
{
	ASSERT							(current->m_parent == cast_node());

	fat_node<pointer_for_fat_size> * const next			=	current->m_next;
	ASSERT							(next);
	fat_node<pointer_for_fat_size> * const next_of_next	=	next->m_next;
	fat_node<pointer_for_fat_size> * const prev			=	current->m_prev;
	
	if ( !prev )
	{
		ASSERT						(current == m_first_child);
		m_first_child			=	next;
	}

	if ( prev )
		prev->m_next			=	next;

	next->m_prev				=	prev;
	next->m_next				=	current;
	current->m_prev				=	next;
	current->m_next				=	next_of_next;

	if ( next_of_next )
		next_of_next->m_prev	=	current;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_folder_node<pointer_for_fat_size>::reverse_bytes ()
{
	vostok::fs::reverse_bytes			(m_first_child);
	m_base.reverse_bytes			();
}

//-----------------------------------------------------------------------------------
// fat_db_file_node_base implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_file_node_base<pointer_for_fat_size>::reverse_bytes ()
{
	vostok::fs::reverse_bytes			(m_resource_base);
	vostok::fs::reverse_bytes			(m_pos);
	vostok::fs::reverse_bytes			(m_size);
	vostok::fs::reverse_bytes			(m_hash);
}

//-----------------------------------------------------------------------------------
// fat_db_hard_link_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_hard_link_node<pointer_for_fat_size>::reverse_bytes ()
{
	vostok::fs::reverse_bytes			(m_reference_node);
	m_base.reverse_bytes			();
}

//-----------------------------------------------------------------------------------
// fat_db_soft_link_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_soft_link_node<pointer_for_fat_size>::reverse_bytes ()
{
	vostok::fs::reverse_bytes			(m_relative_path_to_referenced);
	m_base.reverse_bytes			();
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_soft_link_node<pointer_for_fat_size>::absolute_path_to_referenced	(path_string * out_path) const
{
	path_string								full_path;
	cast_node()->get_full_path				(full_path);
	directory_part_from_path				(out_path, full_path.c_str());	
	bool const append_result			=	append_relative_path(out_path, m_relative_path_to_referenced);
	R_ASSERT_U								(append_result);
}

//-----------------------------------------------------------------------------------
// fat_db_file_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_file_node<pointer_for_fat_size>::reverse_bytes ()
{
	fat_db_file_node_base<pointer_for_fat_size>::reverse_bytes	();
	m_base.reverse_bytes			();
}

//-----------------------------------------------------------------------------------
// fat_db_compressed_file_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_compressed_file_node<pointer_for_fat_size>::reverse_bytes ()
{
	fat_db_file_node_base<pointer_for_fat_size>::reverse_bytes	();
	vostok::fs::reverse_bytes			(m_uncompressed_size);
	m_base.reverse_bytes			();
}

//-----------------------------------------------------------------------------------
// fat_inline_base implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_inline_base<pointer_for_fat_size>::reverse_bytes ()
{
	vostok::fs::reverse_bytes			(m_inlined_data);
	vostok::fs::reverse_bytes			(m_inlined_size);
}

template <platform_pointer_enum pointer_for_fat_size>
const_buffer   fat_inline_base<pointer_for_fat_size>::get_inlined_data () const 
{ 
	return							const_buffer((pcstr)m_inlined_data, m_inlined_size); 
}

//-----------------------------------------------------------------------------------
// fat_db_inline_file_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_inline_file_node<pointer_for_fat_size>::reverse_bytes ()
{
	fat_db_file_node_base<pointer_for_fat_size>::reverse_bytes	();
	fat_inline_base<pointer_for_fat_size>::reverse_bytes();
	m_base.reverse_bytes			();
}

//-----------------------------------------------------------------------------------
// fat_db_compressed_file_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
void   fat_db_inline_compressed_file_node<pointer_for_fat_size>::reverse_bytes ()
{
	fat_db_file_node_base<pointer_for_fat_size>::reverse_bytes	();
	fat_inline_base<pointer_for_fat_size>::reverse_bytes();
	vostok::fs::reverse_bytes			(m_uncompressed_size);
	m_base.reverse_bytes			();
}

//-----------------------------------------------------------------------------------
// fat_node implementation
//-----------------------------------------------------------------------------------

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::operator == (fat_node<pointer_for_fat_size> const & n) const
{
	R_ASSERT							(!is_link() && !n.is_link(), "this can be fixed. Call Lain");

	if ( get_flags() != n.get_flags() )
		return							false;

	fat_folder_node<pointer_for_fat_size> const * f1	=	 cast_folder();
	fat_folder_node<pointer_for_fat_size> const * f2	=	 n.cast_folder();

	if ( (f1!=NULL) != (f2!=NULL) )
		return false;

	if ( f1 && f2 )
	{
		fat_node<pointer_for_fat_size> const * child1			=	f1->get_first_child();
		while ( child1 )
		{
			fat_node<pointer_for_fat_size> const * child2		=	f2->find_child(child1->m_name);
			if ( !child2 || !(*child1 == *child2) )
				return				false;
			
			child1				=	child1->get_next();
		}
	}

	return true;
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::same_path (fat_node const * n) const
{
	if ( !strings::equal(m_name, n->m_name) )
		return						false;
	
	if ( (m_parent==NULL) != (n->m_parent==NULL) )
		return						false;
	
	if ( !m_parent )
		return						true;

	return							(m_parent == n->m_parent) || m_parent->same_path(n->m_parent);
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_file_size () const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
	{
		return						referenced_node->get_file_size();
	}
	else if ( !is_folder() )
	{
		if ( is_db() )
		{
			if ( is_inlined() )
			{
				return				is_compressed() ?	cast_db_inline_compressed_file()->m_uncompressed_size : 
														cast_db_inline_file()->m_size;
			}
			else
			{
				return				is_compressed() ?	cast_db_compressed_file()->m_uncompressed_size : 
														cast_db_file()->m_size;
			}			
		}

		return						cast_disk_file()->size();
	}

	return							0;
}

static
bool   current_thread_locked_fat_for_read ()
{
	resources::thread_local_data * const tls	=	resources::g_resources_manager->get_thread_local_data
														(threading::current_thread_id(), false);
	if ( !tls )
		return								false;
	return									tls->locked_fat_for_read;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::find_referenced_link_node () const
{
	if ( !is_link() )
		return								NULL;

	if ( is_hard_link() )
	{
		fat_node<pointer_for_fat_size> * const out_referenced_node	=	cast_db_hard_link_node()->reference_node();
		return								out_referenced_node;
	}

	u32 const thread_id					=	threading::current_thread_id();
	R_ASSERT_U								(thread_id == resources::g_resources_manager->resources_thread_id() || 
											 thread_id == resources::g_resources_manager->mount_and_fs_iterator_dispatch_mutex_hold_thread_id() || 
											 current_thread_locked_fat_for_read());

	path_string								full_path;
	cast_db_soft_link_node()->absolute_path_to_referenced	(& full_path);

	fat_node<pointer_for_fat_size> * const out_referenced_node	=	
		(fat_node<pointer_for_fat_size> *)g_fat->impl()->find_node_no_mount(full_path.c_str());
	
	R_ASSERT								(out_referenced_node);

	return									out_referenced_node;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::find_link_target_path (path_string * out_path) const
{
	ASSERT									(is_link());
	if ( is_hard_link() )
	{
		fat_node<pointer_for_fat_size> * const referenced_node	=	cast_db_hard_link_node()->reference_node();
		referenced_node->get_full_path		(* out_path);
		return;
	}

	cast_db_soft_link_node()->absolute_path_to_referenced	(out_path);
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_raw_file_size () const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
	{
		return						referenced_node->get_raw_file_size();
	}
	else if ( !is_folder() )
	{
		if ( is_db() )
		{
			if ( is_inlined() )
			{
				return				is_compressed() ?	cast_db_inline_compressed_file()->size() : 
														cast_db_inline_file()->size();
			}
			else
			{
				return				is_compressed() ?	cast_db_compressed_file()->size() :
														cast_db_file()->size();
			}
		}

		return						cast_disk_file()->size();
	}

	return							0;
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_compressed_file_size	() const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
		return						referenced_node->get_compressed_file_size();
	
	CURE_ASSERT						(is_compressed(), return 0);
	return							get_raw_file_size();
}

template <platform_pointer_enum pointer_for_fat_size>
typename fat_node<pointer_for_fat_size>::file_size_type   fat_node<pointer_for_fat_size>::get_file_offs () const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
	{
		return						referenced_node->get_file_offs();
	}
	else if ( !is_folder() )
	{
		if ( is_db() )
		{
			if ( is_inlined() )
			{
				LOG_ERROR			( "you should not call get_file_offs over inline node" );
				UNREACHABLE_CODE	(
					is_compressed() ?
						cast_db_inline_compressed_file()->offs_in_db() : 
						cast_db_inline_file()->offs_in_db()
				);
			}
			else
			{
				return				is_compressed() ?	cast_db_compressed_file()->offs_in_db() : 
														cast_db_file()->offs_in_db();
			}
		}

		return						0;
	}

	return							0;
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::get_hash (u32 * out_hash) const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
		return						referenced_node->get_hash(out_hash);
	
	* out_hash					=	0;
	if ( is_folder() )
		return						false;

	if ( !is_db() )
		return						false;

	if ( is_inlined() )
	{
		* out_hash				=	is_compressed() ?	cast_db_inline_compressed_file()->hash() : 
														cast_db_inline_file()->hash();
	}
	else
	{
		* out_hash				=	is_compressed() ?	cast_db_compressed_file()->hash() : 
														cast_db_file()->hash();
	}

	return							true;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::set_hash (u32 hash)
{
	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
	{
		referenced_node->set_hash	(hash);
		return;
	}
	
	R_ASSERT						(!is_folder());
	R_ASSERT						(is_db());

	if ( is_inlined() )
	{
		if ( is_compressed() )
			cast_db_inline_compressed_file()->set_hash(hash);
		else
			cast_db_inline_file()->set_hash(hash);
	}
	else
	{
		if ( is_compressed() )
			cast_db_compressed_file()->set_hash(hash);
		else
			cast_db_file()->set_hash(hash);
	}
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_num_children () const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
		return						referenced_node->get_num_children();

	if ( !is_folder() )
		return						0;

	u32	num						=	0;

	fat_node const *	cur_child	=	cast_folder()->get_first_child();
	while ( cur_child )
	{
		++num;
		cur_child				=	cur_child->get_next();
	}

	return num;
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_num_nodes () const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
		return						referenced_node->get_num_nodes();

	R_ASSERT						(!is_link());
	u32	num						=	1;

	if ( is_folder() )
	{
		fat_node<pointer_for_fat_size> const *	cur_child	=	cast_folder()->get_first_child();
		while ( cur_child )
		{
			num					+=	cur_child->get_num_nodes();
			cur_child			=	cur_child->get_next();
		}
	}

	return num;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::get_num_nodes (u32 & num_folders, u32 & num_files) const
{
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
	{
		return						referenced_node->get_num_nodes(num_folders, num_files);
	}

	num_folders	=	0;
	num_files	=	0;
	if ( is_folder() )
	{
		++num_folders;
		for ( fat_node const *	child	=	get_first_child(); 
								child	!=	NULL;
								child	=	child->get_next() )
		{
			u32 child_folders, child_files;
			child->get_num_nodes	(child_folders, child_files);
			num_folders		+=	child_folders;
			num_files		+=	child_files;
		}
	}
	else
		++num_files;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::get_first_child (bool skip_erased)
{
	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
		return						referenced_node->get_first_child(skip_erased);

	if ( is_folder() ) 
		return	cast_folder()->get_first_child(skip_erased); 

	return							NULL;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::get_next (bool skip_erased)       
{ 
	if ( !skip_erased )
		return						m_next;

	fat_node<pointer_for_fat_size> *   out_node	=	m_next;
	while ( out_node && is_erased_node(out_node) )
		out_node				=	out_node->m_next;

	return							out_node; 
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_max_fat_size (fat_inline_data const & inline_data, 
														fat_node_info *			info,
														u32 *					out_nodes_count) const
{
	R_ASSERT					(!is_link());
	ASSERT						(out_nodes_count);
	* out_nodes_count		=	0;
	u32 out_size			=	inline_data.total_size_for_extensions_with_limited_size();
	return						out_size + get_max_fat_size_impl(inline_data, info, info, out_nodes_count);
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_max_fat_size_impl (fat_inline_data const &	inline_data, 
															 fat_node_info *			info,
															 fat_node_info *			root_info,
															 u32 *						out_nodes_count) const
{
	R_ASSERT					(!is_link());
	if ( !info->same_color(root_info) )
		return					0;

	++ * out_nodes_count;

	u32 const max_node_size	=	(u32)math::max(	math::max(	sizeof(fat_db_file_node<pointer_for_fat_size>),
															sizeof(fat_folder_node<pointer_for_fat_size>) ),
															sizeof(fat_db_compressed_file_node<pointer_for_fat_size>)	);
		
	u32 size				=	max_node_size;
	size					+=	strings::length(m_name) + 1;
	size					+=	sizeof(void*);

	if ( !is_folder() )
	{
		pcstr extension		=	extension_from_path(m_name);
		fat_inline_data::item const * item	=	NULL;
		if ( inline_data.find_by_extension(& item, extension) && (item->current_size == fat_inline_data::item::no_limit) )
		{
			size			+=	get_file_size();
			size			+=	VOSTOK_DEFAULT_ALIGN_SIZE; // may need alignment
		}
	}

	fat_node const *	cur_child	=	get_first_child();
	fat_node_info *	info_child	=	info->first_child;
	while ( cur_child )
	{
		size				+=	cur_child->get_max_fat_size_impl (inline_data, info_child, info_child, out_nodes_count);
		cur_child			=	cur_child->get_next();
		info_child			=	info_child->next;
	}

	return						size;
}

static resources::base_of_intrusive_base *    assign_and_return_result (resources::base_of_intrusive_base * & target,
																		resources::base_of_intrusive_base * source)
{
	target	=	source;
	return		source;
}

template <platform_pointer_enum pointer_for_fat_size>
resources::resource_base * &   fat_node<pointer_for_fat_size>::ref_associated_ptr()
{
	static resources::resource_base * s_zero = NULL;
	CURE_ASSERT						(!is_folder(), return s_zero);

	if ( is_link() )
	{
		fat_node<pointer_for_fat_size> * const referenced	=	find_referenced_link_node();
		return						referenced->ref_associated_ptr();
	}
	else if ( is_db() )
	{
		if ( is_inlined() )
		{
			return					is_compressed() ? 	cast_db_inline_compressed_file()->m_resource_base :
													  	cast_db_inline_file()->m_resource_base;
		}
		else
		{
			return					is_compressed() ?	cast_db_compressed_file()->m_resource_base : 
														cast_db_file()->m_resource_base;
		}
	}

	return							cast_disk_file()->m_resource_base;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::lock_associated () const
{
	threading::atomic32_value_type unlocked_value	=	0;
	threading::atomic32_value_type locked_value		=	0;

	do {
		unlocked_value	=	ref_flags_as_32bit() & ~(file_system::is_locked << detail::bits_to_flags_byte());
		locked_value	=	unlocked_value		 |	(file_system::is_locked << detail::bits_to_flags_byte());

	} while ( threading::interlocked_compare_exchange(ref_flags_as_32bit(), locked_value, unlocked_value) != unlocked_value );
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::unlock_associated () const
{
	threading::atomic32_value_type unlocked_value	=	0;
	threading::atomic32_value_type locked_value		=	0;

	do {
		locked_value	=	ref_flags_as_32bit();
		R_ASSERT			(locked_value & 
							(file_system::is_locked << detail::bits_to_flags_byte()));

		unlocked_value	=	locked_value & ~(file_system::is_locked << detail::bits_to_flags_byte());

	} while ( threading::interlocked_compare_exchange(ref_flags_as_32bit(), unlocked_value, locked_value) != locked_value );
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::set_associated (resources::resource_base * const resource)
{
	R_ASSERT								(! is_folder());

	COMPILE_ASSERT							(sizeof(long) == sizeof(u32),
											 use_32_bit_version_of_interlocked_or_on_this_platform);

	lock_associated							();

	resources::resource_base * & res_base	=	ref_associated_ptr();
	threading::interlocked_exchange_pointer	((pvoid&)res_base, resource);

	unlock_associated						();
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::try_clean_associated (u32 const allow_reference_count)
{
	R_ASSERT								(! is_folder());
	lock_associated							();

	resources::resource_base * & res_base	=	ref_associated_ptr();
	resources::base_of_intrusive_base * base_of_intrusive_base	=	NULL;

	bool cleaned						=	false;
	if ( res_base 
		 && assign_and_return_result(base_of_intrusive_base, res_base->cast_base_of_intrusive_base()) 
		 && (u32)base_of_intrusive_base->get_reference_count() == reference_count )
	{
		threading::interlocked_exchange_pointer	((pvoid&)res_base, NULL);
		cleaned							=	true;
	}

	unlock_associated						();
	return									cleaned;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::get_associated_ptr_helper (resources::managed_resource_ptr *		result_managed, 
																  resources::unmanaged_resource_ptr *	result_unmanaged,
																  resources::query_result *	*			result_query_result)
{
	lock_associated							();
	resources::resource_base * res_base	=	get_associated_unsecure ();
	resources::base_of_intrusive_base * base_of_intrusive_base	=	NULL;
	
	if ( (result_managed || result_unmanaged) &&
		 res_base &&
		 assign_and_return_result(base_of_intrusive_base, res_base->cast_base_of_intrusive_base()) &&
		 base_of_intrusive_base->get_reference_count() != 0 )
	{
		if ( result_managed )
			* result_managed			=	res_base->cast_managed_resource();
		else
			* result_unmanaged			=	res_base->cast_unmanaged_resource();
	}
	else if ( result_query_result && res_base )
	{
		* result_query_result			=	res_base->cast_query_result();
	}

	unlock_associated						();
}

template <platform_pointer_enum pointer_for_fat_size>
resources::unmanaged_resource_ptr   fat_node<pointer_for_fat_size>::get_associated_unmanaged_resource_ptr ()
{
	resources::unmanaged_resource_ptr		result;
	get_associated_ptr_helper				(NULL, & result, NULL);
	return									result;
}

template <platform_pointer_enum pointer_for_fat_size>
resources::managed_resource_ptr   fat_node<pointer_for_fat_size>::get_associated_managed_resource_ptr ()
{
	resources::managed_resource_ptr			result;
	get_associated_ptr_helper				(& result, NULL, NULL);
	return									result;
}

template <platform_pointer_enum pointer_for_fat_size>
resources::query_result *   fat_node<pointer_for_fat_size>::get_associated_query_result () 
{
	resources::query_result *				result	=	NULL;
	get_associated_ptr_helper				(NULL, NULL, & result);
	return									result;
}
												
template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::get_inline_data (const_buffer * out_buffer) const
{		
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
		return								referenced_node->get_inline_data(out_buffer);

	if ( !is_inlined() )
		return								false;

	if ( is_compressed() )
		* out_buffer					=	cast_db_inline_compressed_file()->get_inlined_data();
	else
		* out_buffer					=	cast_db_inline_file()->get_inlined_data();

	return									true;
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::has_flags_follow_link (u32 flags) const
{ 
	if ( fat_node<pointer_for_fat_size> const * const referenced_node = find_referenced_link_node() ) 
		return								referenced_node->has_flags(flags);

	return									has_flags(flags); 
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::set_inline_data (const_buffer const & buffer)
{
	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
		return								referenced_node->set_inline_data	(buffer);
	
	CURE_ASSERT								(is_inlined(), return false);

	if ( is_compressed() )
	{
		fat_db_inline_compressed_file_node<pointer_for_fat_size> * const inline_compressed_file	=	cast_db_inline_compressed_file();
		ASSERT								(inline_compressed_file);
		inline_compressed_file->set_inlined_data	(buffer);
	}
	else
	{
		fat_db_inline_file_node<pointer_for_fat_size> * const inline_file	=	cast_db_inline_file();
		ASSERT								(inline_file);
		inline_file->set_inlined_data		(buffer);
	}

	return									true;
}

template <platform_pointer_enum pointer_for_fat_size>
resources::resource_base *   fat_node<pointer_for_fat_size>::get_associated_unsecure () const
{
	fat_node * non_const_this			=	const_cast< fat_node<pointer_for_fat_size> *>(this);
	return									non_const_this->ref_associated_ptr	();
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::is_associated () const
{
	lock_associated							();

	resources::resource_base * const res_base	=	get_associated_unsecure ();
	resources::base_of_intrusive_base * base_of_intrusive_base	=	NULL;

	bool out_result						=	true;
	if ( !res_base )
		out_result						=	false;
	else if ( assign_and_return_result(base_of_intrusive_base, res_base->cast_base_of_intrusive_base()) )
		out_result						=	base_of_intrusive_base->get_reference_count() != 0;
	else
		out_result						=	true; // its query_result

	unlock_associated						();

	return									out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::is_associated_with (resources::resource_base * const resource_base) const
{
	lock_associated							();
	bool const out_result				=	(get_associated_unsecure () == resource_base);
	unlock_associated						();
	return									out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_folder_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_folder ()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return								referenced_node->cast_folder();
	R_ASSERT								(!is_link());

	if ( !is_folder() )
		return								NULL;

	if ( !is_disk() )
	{
		fat_folder_node<pointer_for_fat_size> *	out_result	=	NULL;
		size_t const offs				=	(char *)(& out_result->m_base) - (char *)(out_result);

		out_result						=	(fat_folder_node<pointer_for_fat_size> *)((char *)(this) - offs);
		return								out_result;
	}

	fat_disk_folder_node<pointer_for_fat_size> * const disk_folder	=	cast_disk_folder();
	fat_folder_node<pointer_for_fat_size> *	const out_result	=	disk_folder->cast_folder_node();
	return									out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_disk_folder_node<pointer_for_fat_size>*   fat_node<pointer_for_fat_size>::cast_disk_folder ()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return								referenced_node->cast_disk_folder();
	R_ASSERT							(!is_link());

	if ( !is_folder() || !is_disk() )
		return							NULL;

	fat_disk_folder_node<pointer_for_fat_size> * out_result =	NULL;
	size_t const offs				=	(char*)(& out_result->m_folder.m_base) - (char *)(out_result);

	out_result						=	(fat_disk_folder_node<pointer_for_fat_size>*)((char*)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_disk_file_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_disk_file	()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return								referenced_node->cast_disk_file();
	R_ASSERT							(!is_link());

	if ( !is_disk() || is_folder() )
		return							 NULL;

	fat_disk_file_node<pointer_for_fat_size> * out_result		=	NULL;
	size_t const offs				=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_disk_file_node<pointer_for_fat_size> *)((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_db_file_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_db_file	()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return							referenced_node->cast_db_file();
	R_ASSERT							(!is_link());

	if ( is_folder() || !is_db() || is_compressed() )
		return							 NULL;

	fat_db_file_node<pointer_for_fat_size> * out_result	=	NULL;
	size_t const offs				=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_db_file_node<pointer_for_fat_size> *)((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_db_compressed_file_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_db_compressed_file ()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return							referenced_node->cast_db_compressed_file();
	R_ASSERT							(!is_link());

	if ( is_folder() || !is_db() || !is_compressed() )
		return						 NULL;

	fat_db_compressed_file_node<pointer_for_fat_size> * out_result	=	NULL;
	size_t const offs				=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_db_compressed_file_node<pointer_for_fat_size> *)((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_db_inline_file_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_db_inline_file ()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return							referenced_node->cast_db_inline_file();
	R_ASSERT							(!is_link());

	if ( is_folder() || !is_db() || is_compressed() || !is_inlined() )
		return							 NULL;

	fat_db_inline_file_node<pointer_for_fat_size> * out_result			=	NULL;
	size_t const offs				=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_db_inline_file_node<pointer_for_fat_size> *)((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_db_inline_compressed_file_node<pointer_for_fat_size> *	 fat_node<pointer_for_fat_size>::cast_db_inline_compressed_file ()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return							referenced_node->cast_db_inline_compressed_file();
	R_ASSERT							(!is_link());

	if ( is_folder() || !is_db() || !is_compressed() || !is_inlined() )
		return							NULL;

	fat_db_inline_compressed_file_node<pointer_for_fat_size> * out_result			=	NULL;
	size_t	offs					=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_db_inline_compressed_file_node<pointer_for_fat_size> *)	((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_db_soft_link_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_db_soft_link_node ()
{
	if ( !is_soft_link() )
		return							NULL;

	fat_db_soft_link_node<pointer_for_fat_size> * out_result	=	NULL;
	size_t	offs					=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_db_soft_link_node<pointer_for_fat_size> *)	((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_db_hard_link_node<pointer_for_fat_size> *   fat_node<pointer_for_fat_size>::cast_db_hard_link_node ()
{
	if ( !is_hard_link() )
		return							NULL;

	fat_db_hard_link_node<pointer_for_fat_size> * out_result	=	NULL;
	size_t	offs					=	(char *)(& out_result->m_base) - (char *)(out_result);

	out_result						=	(fat_db_hard_link_node<pointer_for_fat_size> *)	((char *)(this) - offs);
	return								out_result;
}

template <platform_pointer_enum pointer_for_fat_size>
fat_disk_node_base *   fat_node<pointer_for_fat_size>::cast_disk_node_base ()
{
// 	if ( fat_node<pointer_for_fat_size> * const referenced_node = find_referenced_link_node() ) 
// 		return							referenced_node->cast_disk_node_base();
	R_ASSERT							(!is_link());

	if ( fat_disk_folder_node<pointer_for_fat_size> * const folder = cast_disk_folder() )
		return							folder;
	else if ( fat_disk_file_node<pointer_for_fat_size> * const file = cast_disk_file() )
		return							file;

	return								NULL;
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::get_full_path (path_string & str) const
{
	u32			path_part_lengths		[64];
	u32			num_path_parts		=	0;

	u32			size				=	0;
	fat_node const * parent			=	this;

	while ( parent && parent->m_name[0] )
	{
		u32 const path_part_length			=	strings::length (parent->m_name);
		path_part_lengths[num_path_parts]	=	path_part_length;
		++num_path_parts;

		size						+=	path_part_length + 1;
		parent						=	parent->m_parent;
	}

	if ( num_path_parts )
		--size; // the last doesnt have '/' separator

	ASSERT								(size < str.max_length());

	str.set_length						(size);

	u32		path_part				=	0;
	u32		index					=	size;
	parent							=	this;
	char*	buffer					=	str.get_buffer();
	while ( parent && parent->m_name[0] )
	{
		const u32 path_part_length	=	path_part_lengths[path_part];

		index						-=	path_part_length;
		memory::copy					(buffer+index, path_part_length, parent->m_name, path_part_length);
		++path_part;
		parent						=	parent->m_parent;
		if ( parent && parent->m_name[0] )
		{
			--index;
			buffer[index]			=	'/';
		}
	}
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::reverse_bytes()
{
	vostok::fs::reverse_bytes				(m_flags);
	vostok::fs::reverse_bytes				(m_next);
	vostok::fs::reverse_bytes				(m_prev);
	vostok::fs::reverse_bytes				(m_parent);
}

template <platform_pointer_enum pointer_for_fat_size>
void   fat_node<pointer_for_fat_size>::reverse_bytes_for_real_class ()
{
	if ( is_soft_link() )
	{
		fat_db_soft_link_node<pointer_for_fat_size> * const link	=	cast_db_soft_link_node();
		link->reverse_bytes		();
	}
	else if ( is_hard_link() )
	{
		fat_db_hard_link_node<pointer_for_fat_size> * const link	=	cast_db_hard_link_node();
		link->reverse_bytes		();
	}
	else if ( is_folder() )
	{
		if ( is_db() )
		{
			fat_folder_node<pointer_for_fat_size> * const folder	=	cast_folder();
			ASSERT						(folder);
			folder->reverse_bytes		();
		}
		else
			UNREACHABLE_CODE();
	}
	else if ( is_inlined() )
	{
		if ( is_compressed() )
		{
			fat_db_inline_compressed_file_node<pointer_for_fat_size> * const compressed_inline_file =	cast_db_inline_compressed_file();
			ASSERT										(compressed_inline_file);
			compressed_inline_file->reverse_bytes		();
		}
		else
		{
			fat_db_inline_file_node<pointer_for_fat_size> * inline_file	=	cast_db_inline_file();
			ASSERT							(inline_file);
			inline_file->reverse_bytes		();
		}
	}
	else
	{
		if ( is_disk() )
		{
			UNREACHABLE_CODE();
		}
		else if ( is_compressed() )
		{
			fat_db_compressed_file_node<pointer_for_fat_size> * const compressed_file	=	cast_db_compressed_file();
			ASSERT							(compressed_file);
			compressed_file->reverse_bytes	();
		}
		else
		{
			fat_db_file_node<pointer_for_fat_size> * const db_file	=	cast_db_file();
			ASSERT							(db_file);
			db_file->reverse_bytes			();
		}
	}
}

template <platform_pointer_enum pointer_for_fat_size>
threading::atomic32_type &   fat_node<pointer_for_fat_size>::ref_flags_as_32bit () const
{
	return									(threading::atomic32_type &)m_flags;
}

template <platform_pointer_enum pointer_for_fat_size>
u32   fat_node<pointer_for_fat_size>::get_sizeof () const
{
	if ( is_soft_link() )
		return								sizeof(fat_db_soft_link_node<pointer_for_fat_size>);
	if ( is_hard_link() )
		return								sizeof(fat_db_hard_link_node<pointer_for_fat_size>);

	if ( is_folder() )
	{
		if ( is_disk() )
			return							sizeof(fat_disk_folder_node<pointer_for_fat_size>);
		return								sizeof(fat_folder_node<pointer_for_fat_size>);
	}
	if ( is_compressed() )
		return								sizeof(fat_db_compressed_file_node<pointer_for_fat_size>);

	return									sizeof(fat_db_file_node<pointer_for_fat_size>);
}

template <platform_pointer_enum pointer_for_fat_size>
bool   fat_node<pointer_for_fat_size>::is_root_of_sub_fat () const
{
	NOT_IMPLEMENTED							(return false);
}

template <>
bool   fat_node<platform_pointer_default>::is_root_of_sub_fat () const
{
	sub_fat_resource * const sub_fat	=	g_fat->impl()->get_db(this);
	if ( sub_fat && sub_fat->root_node == this )
		return								true;

	return									false;
}

void   fat_disk_node_base::set_node_is_locked (bool lock)	
{ 
	if ( lock )	
		threading::interlocked_increment	(m_node_lock_count);
	else			
	{
		R_ASSERT							(m_node_lock_count);
		threading::interlocked_decrement	(m_node_lock_count);
	}
}

void   set_fat_node_is_locked (fat_node<> * node, bool lock)
{
	if ( !node->is_disk() )
		return;

	if ( fat_disk_file_node<> * disk_node = node->cast_disk_file() )
		disk_node->set_node_is_locked		(lock);
	else if ( fat_disk_folder_node<> * disk_folder = node->cast_disk_folder() )
		disk_folder->set_node_is_locked		(lock);
}

template class fat_node						<platform_pointer_32bit>;
template class fat_node						<platform_pointer_64bit>;
template class fat_folder_node				<platform_pointer_32bit>;
template class fat_folder_node				<platform_pointer_64bit>;
template class fat_disk_folder_node			<platform_pointer_32bit>;
template class fat_disk_folder_node			<platform_pointer_64bit>;
template class fat_disk_file_node			<platform_pointer_32bit>;
template class fat_disk_file_node			<platform_pointer_64bit>;
template class fat_db_file_node				<platform_pointer_32bit>;
template class fat_db_file_node				<platform_pointer_64bit>;
template class fat_db_compressed_file_node	<platform_pointer_32bit>;
template class fat_db_compressed_file_node	<platform_pointer_64bit>;

} // namespace fs 
} // namespace vostok 