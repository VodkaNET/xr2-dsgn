////////////////////////////////////////////////////////////////////////////
//	Created		: 16.02.2011
//	Author		: Sergey Pryshchepa
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "animations_view_panel.h"
#include "animations_view_source.h"
#include "animation_lexeme_editor.h"

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using System::Windows::Forms::TreeNode;
using vostok::animation_editor::animations_view_panel;

void animations_view_panel::in_constructor()
{
	vostok::editor_base::image_loader	loader;
	tree_view_image_list = loader.get_shared_images16();
	tree_view_image_list->TransparentColor = System::Drawing::Color::Transparent;

	m_context_menu = gcnew System::Windows::Forms::ContextMenuStrip();
	m_raw_files_tree_view->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &animations_view_panel::on_tree_node_mouse_click);
	m_raw_files_tree_view->ImageList = tree_view_image_list;
	m_raw_files_tree_view->source = gcnew animations_view_source();
	m_raw_files_tree_view->refresh();
	extension = ".clip";
	HideOnClose = true;
	last_selected_node = nullptr;
}

void animations_view_panel::on_node_double_click(System::Object^, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e)
{
	if(safe_cast<tree_node^>(e->Node)->m_node_type==tree_node_type::single_item)
	{
		System::String^ full_path = e->Node->FullPath->Remove(0,11);
		m_editor->add_animation(full_path, safe_cast<bool>(e->Node->Tag));
	}
}

void animations_view_panel::on_node_key_down(System::Object^, System::Windows::Forms::KeyEventArgs^ e)
{
	if(e->KeyCode==Keys::Return)
	{
		TreeNode^ n = m_raw_files_tree_view->SelectedNode;
		if(n->Nodes->Count==0)
		{
			System::String^ full_path = n->FullPath->Remove(0,11);
			m_editor->add_animation(full_path, safe_cast<bool>(n->Tag));
		}
	}
}

void animations_view_panel::track_active_item(System::String^ path)
{
	m_raw_files_tree_view->track_active_node("animations/"+path);
	last_selected_node = m_raw_files_tree_view->selected_nodes[0];
}

void animations_view_panel::on_tree_node_mouse_click(System::Object^, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e)
{
	last_selected_node = e->Node;
}
