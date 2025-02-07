////////////////////////////////////////////////////////////////////////////
//	Created		: 22.01.2010
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "tree_view.h"
#include "tree_node.h"
#include "tree_view_filter_panel.h"
#include "tree_view_search_panel.h"
#include "tree_node_alphanum_comparer.h"

using namespace System::IO;
using namespace System::Windows::Forms;

using System::Reflection::BindingFlags;

namespace vostok
{
namespace editor
{
namespace controls
{

						tree_view::tree_view()
{
	if(!DesignMode)
	{
		
		is_selectable_groups					= true;
		this->PathSeparator						= "/";
		m_selected_nodes						= gcnew Collections::Generic::List<tree_node^>();

		m_tree_view_container					= gcnew Panel();
		m_filter_panel							= gcnew tree_view_filter_panel();
		m_filter_panel->Visible					= false;
		m_filter_panel->Dock					= DockStyle::Bottom;
		m_filter_panel->m_parent_tree_view		= this;
		m_search_panel							= gcnew tree_view_search_panel();
		m_search_panel->Dock					= DockStyle::Top;
		m_search_panel->Visible					= false;
		m_search_panel->m_parent_tree_view		= this;
		m_tree_view_container->Controls->Add	(m_filter_panel);
		m_tree_view_container->Controls->Add	(m_search_panel);

		this->GetType()->
					 GetProperty("DoubleBuffered", BindingFlags::NonPublic|BindingFlags::Instance|BindingFlags::Public)->
					 SetValue(this, true, nullptr);

		m_root				= gcnew tree_node( );
		m_root->m_node_type	= tree_node_type::group_item;

		m_root->GetType( )->GetField( "treeView", BindingFlags::Instance | BindingFlags::NonPublic )->SetValue( m_root, this );
		this->GetType( )->GetField( "root", BindingFlags::Instance | BindingFlags::NonPublic )->SetValue( this, m_root );

		//this->m_nodes_context_menu				= (gcnew System::Windows::Forms::ContextMenuStrip());
		//this->add_folder_menu_item				= (gcnew System::Windows::Forms::ToolStripMenuItem());
		//this->add_file_menu_item				= (gcnew System::Windows::Forms::ToolStripMenuItem());
		//this->remove_menu_item					= (gcnew System::Windows::Forms::ToolStripMenuItem());
		//this->m_nodes_context_menu->SuspendLayout		();
		//this->SuspendLayout						();
		//this->m_nodes_context_menu->Items->AddRange	(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) 
		//											{this->add_folder_menu_item, 
		//											this->add_file_menu_item,
		//											this->remove_menu_item});
		//this->m_nodes_context_menu->Name				= L"m_context_menu";
		//this->m_nodes_context_menu->Size				= System::Drawing::Size(153, 92);

		//this->add_folder_menu_item->Name		= L"add_folder_menu_item";
		//this->add_folder_menu_item->Size		= System::Drawing::Size(152, 22);
		//this->add_folder_menu_item->Text		= L"Add folder";
		//this->add_folder_menu_item->Click		+= gcnew System::EventHandler(this, &tree_view::create_group);

		//this->add_file_menu_item->Name			= L"add_file_menu_item";
		//this->add_file_menu_item->Size			= System::Drawing::Size(152, 22);
		//this->add_file_menu_item->Text			= L"Add item";
		//this->add_file_menu_item->Click			+= gcnew System::EventHandler(this, &tree_view::create_item);

		//this->remove_menu_item->Name			= L"remove_menu_item";
		//this->remove_menu_item->Size			= System::Drawing::Size(152, 22);
		//this->remove_menu_item->Text			= L"Remove item";
		//this->remove_menu_item->Click			+= gcnew System::EventHandler(this, &tree_view::remove_item);

		this->TreeViewNodeSorter				= gcnew tree_node_alphanum_comparer();
		//this->m_nodes_context_menu->ResumeLayout		(false);
		//this->ResumeLayout						(false);
	}
}

void					tree_view::OnParentChanged			(EventArgs^ e)
{
	if(DesignMode || m_b_container_created)
	{
		TreeView::OnParentChanged(e);
		return;
	}
	
	m_b_container_created					= true;
	m_tree_view_container->Location			= this->Location;
	m_tree_view_container->Size				= this->Size;
	if(this->Dock == DockStyle::None)
		m_tree_view_container->Anchor		= this->Anchor;
	else
		m_tree_view_container->Dock			= this->Dock;

	Control^ parent = Parent;
	parent->SuspendLayout();

	Int32 child_index						= parent->Controls->GetChildIndex(this);
	parent->Controls->Remove				(this);

	Boolean filter_visible					= m_filter_panel->Visible;
	parent->Controls->Add					(m_tree_view_container);
	parent->Controls->SetChildIndex			(m_tree_view_container, child_index);
	m_filter_panel->Visible					= filter_visible;

	TreeView::OnParentChanged(e);

	this->Dock										= DockStyle::Fill;
	m_tree_view_container->Controls->Add			(this);
	m_tree_view_container->Controls->SetChildIndex	(this, 0);

	parent->ResumeLayout();
}

}//namespace controls
}//namespace editor
}//namespace vostok