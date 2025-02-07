////////////////////////////////////////////////////////////////////////////
//	Created		: 07.04.2011
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "animation_groups_controllers_tree_files_source.h"
#include <vostok/fs_watcher.h>
#include "animations_list_files_source.h"
#include "animation_editor.h"

using vostok::animation_editor::animation_groups_controllers_tree_files_source;
using System::Windows::Forms::TreeNode;
using System::Reflection::BindingFlags;
using vostok::animation_editor::animations_list_node_sorter;
using vostok::editor::controls::tree_node;
using vostok::editor::controls::tree_node_type;

animation_groups_controllers_tree_files_source::animation_groups_controllers_tree_files_source()
{
	m_callback = NEW(file_watcher_delegate)(gcnew file_watcher_delegate::Delegate(this, &animation_groups_controllers_tree_files_source::fs_callback));
	m_watcher_subscribe_id	=	vostok::resources::subscribe_watcher(unmanaged_string( animation_editor::animation_controllers_path ).c_str( ), boost::bind(&file_watcher_delegate::callback, m_callback, _1));
}

animation_groups_controllers_tree_files_source::~animation_groups_controllers_tree_files_source()
{
	vostok::resources::unsubscribe_watcher(m_watcher_subscribe_id);
	DELETE(m_callback);
}

void animation_groups_controllers_tree_files_source::fs_callback(vostok::vfs::vfs_notification const& info)
{
	if ( info.type != vostok::vfs::vfs_notification::type_modified)
		refresh();
}

tree_view^ animation_groups_controllers_tree_files_source::parent::get()
{
	return m_parent;
}

void animation_groups_controllers_tree_files_source::parent::set(tree_view^ value)
{
	m_parent = value;
}

void animation_groups_controllers_tree_files_source::refresh()
{
	fs_iterator_delegate* q = NEW(fs_iterator_delegate)(gcnew fs_iterator_delegate::Delegate(this, &animation_groups_controllers_tree_files_source::on_fs_iterator_ready), g_allocator);
	resources::query_vfs_iterator(unmanaged_string( animation_editor::animation_controllers_path ).c_str( ), 
		boost::bind(&fs_iterator_delegate::callback, q, _1), g_allocator, vostok::resources::recursive_true);
}

void animation_groups_controllers_tree_files_source::on_fs_iterator_ready(vostok::vfs::vfs_locked_iterator const & fs_it)
{
	m_parent->nodes->Clear();
	//m_parent->add_group("controllers/", editor_base::folder_closed, editor_base::folder_open);
	//process_fs(fs_it.children_begin(), "controllers/");
	process_fs(fs_it.children_begin(), "");
	m_parent->TreeViewNodeSorter = gcnew animations_list_node_sorter();
	m_parent->Sort();
	TreeNode^ node = m_parent->root;
	node->FirstNode->Expand();
}

void animation_groups_controllers_tree_files_source::process_fs(vostok::vfs::vfs_iterator const & in_it, String^ file_path)
{
	vostok::vfs::vfs_iterator	it			=	in_it;
	while(!it.is_end())
	{
		if(it.is_folder())
		{
			String^ folder_name = gcnew String(it.get_name());
			if(folder_name=="groups")
			{
				++it;
				continue;
			}

			m_parent->add_group(file_path+folder_name, editor_base::folder_closed, editor_base::folder_open);
			process_fs(it.children_begin(), file_path+folder_name+"/");
		}
		else
		{
			if(System::IO::Path::GetExtension(gcnew String(it.get_name())) == ".lua")
			{
				String^ file_name = System::IO::Path::GetFileNameWithoutExtension(gcnew String(it.get_name()));
				m_parent->add_item(file_path+file_name, editor_base::node_resource);
			}
		}
		++it;
	}
}
