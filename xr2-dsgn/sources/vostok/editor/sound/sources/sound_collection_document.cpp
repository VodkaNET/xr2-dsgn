////////////////////////////////////////////////////////////////////////////
//	Created		: 20.06.2011
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "sound_collection_document.h"
#include "sound_document_editor_base.h"
#include "sound_editor.h"
#include "sound_collection_wrapper.h"
#include "single_sound_wrapper.h"
#include "sound_collection_item.h"
#include "sound_collection_commands.h"
#include "tree_view_panel.h"

using vostok::sound_editor::sound_collection_document;
using vostok::sound_editor::sound_editor;
using vostok::sound_editor::sound_collection_item;
using vostok::sound_editor::sound_object_wrapper;
using vostok::sound_editor::sound_object_type;

sound_collection_document::sound_collection_document(sound_editor^ ed)
:super(ed->multidocument_base),
m_editor(ed)
{
	m_name = "new collection";
	m_first_save = true;
	m_command_engine = gcnew command_engine(100);
	m_collection = nullptr;
	SuspendLayout();
	// m_save_file_dialog
	m_save_file_dialog = gcnew SaveFileDialog();
	m_save_file_dialog->AddExtension = true;
	m_save_file_dialog->DefaultExt = ".sound_collection";
	m_save_file_dialog->Filter = "Sound collection files|*.sound_collection";
	m_save_file_dialog->InitialDirectory = System::IO::Path::GetFullPath(sound_editor::absolute_sound_resources_path+"/collections");
	m_save_file_dialog->RestoreDirectory = true;
	m_save_file_dialog->SupportMultiDottedExtensions = true;
	m_save_file_dialog->Title = "Save collection";

	m_context_menu = gcnew System::Windows::Forms::ContextMenuStrip();
	removeToolStripMenuItem = gcnew ToolStripMenuItem();
	addCollectionToolStripMenuItem = gcnew ToolStripMenuItem();

	// m_context_menu
	m_context_menu->SuspendLayout();
	m_context_menu->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>(2) {
		addCollectionToolStripMenuItem,
		removeToolStripMenuItem,
	});
	m_context_menu->Name = L"m_context_menu";
	m_context_menu->Size = System::Drawing::Size(153, 92);
	m_context_menu->Opened += gcnew EventHandler(this, &sound_collection_document::menu_opened);

	// removeToolStripMenuItem
	removeToolStripMenuItem->Name = L"removeItemToolStripMenuItem";
	removeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
	removeToolStripMenuItem->Text = L"Remove item";
	removeToolStripMenuItem->Click += gcnew System::EventHandler(this, &sound_collection_document::remove_click);

	// addCollectionToolStripMenuItem
	addCollectionToolStripMenuItem->Name = L"addCollectionToolStripMenuItem";
	addCollectionToolStripMenuItem->Size = System::Drawing::Size(152, 22);
	addCollectionToolStripMenuItem->Text = L"Add new collection";
	addCollectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &sound_collection_document::add_collection_click);

	m_context_menu->ResumeLayout(false);

	// m_tree_view_image_list
	vostok::editor_base::image_loader	loader;
	m_tree_view_image_list = loader.get_shared_images16();
	m_tree_view_image_list->TransparentColor = System::Drawing::Color::Transparent;

	// m_tree_view
	m_tree_view = gcnew tree_view();
	m_tree_view->AllowDrop = true;
	m_tree_view->ContextMenuStrip = m_context_menu;
	m_tree_view->Dock = System::Windows::Forms::DockStyle::Fill;
	m_tree_view->ImageList = m_tree_view_image_list;
	m_tree_view->is_multiselect = true;
	m_tree_view->Name = L"m_tree_view";
	m_tree_view->TabIndex = 0;
	m_tree_view->DragOver += gcnew DragEventHandler(this, &sound_collection_document::on_drag_over);
	m_tree_view->DragDrop += gcnew DragEventHandler(this, &sound_collection_document::on_drag_drop);
	m_tree_view->selected_items_changed += gcnew EventHandler<vostok::editor::controls::tree_view_selection_event_args^>(this, &sound_collection_document::on_selection_changed);

	AllowEndUserDocking = false;
	AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	ClientSize = System::Drawing::Size(562, 439);
	Controls->Add(m_tree_view);
	VisibleChanged += gcnew System::EventHandler(this, &sound_collection_document::on_document_activated);
	ResumeLayout(false);
}

sound_collection_document::~sound_collection_document()
{
	delete m_command_engine;
	delete m_save_file_dialog;
	delete m_tree_view;
}

void sound_collection_document::save()
{
	if(is_saved)
		return;
	
	if(m_first_save)
	{
		if(m_save_file_dialog->ShowDialog(this)==System::Windows::Forms::DialogResult::OK)
		{
			System::String^ name_with_ext = m_save_file_dialog->FileName->Remove(0, m_save_file_dialog->InitialDirectory->Length+1);
			Name = name_with_ext->Remove(name_with_ext->Length-17)->Replace("\\", "/");
			Text = Name;
			m_collection = gcnew sound_collection_wrapper(this->Name);
			m_collection->save();
			load();
		}

		return;
	}

	m_collection->save();
	m_command_engine->set_saved_flag();
	is_saved = true;
	m_first_save = false;
}

void sound_collection_document::load()
{
	m_collection = safe_cast<sound_collection_wrapper^>(m_editor->get_sound(this->Name, sound_object_type::collection));
	if(m_collection!=nullptr)
	{
		if(m_collection->is_loaded)
			return on_resources_loaded(nullptr, nullptr);

		m_collection->on_loaded += gcnew EventHandler(this, &sound_collection_document::on_resources_loaded);
	}
}

void sound_collection_document::on_resources_loaded(Object^, EventArgs^)
{
	if(m_collection!=nullptr && m_collection->is_loaded)
	{
		m_command_engine->clear_stack();
		m_command_engine->set_saved_flag();
		is_saved = true;
		m_first_save = false;
		m_tree_view->nodes->Clear();
		m_name = this->Name;
		int ind = m_name->LastIndexOf("/");
		if(ind>0)
			m_name = m_name->Remove(0, ind+1);

		tree_node^ n = m_tree_view->add_group(m_name, editor_base::folder_closed, editor_base::folder_open);
		fill_tree_view(n, m_collection->items());
		n->Expand();
	}
}

void sound_collection_document::fill_tree_view(tree_node^ root, items_list^ itms)
{
	for each(sound_collection_item^ itm in itms)
	{
		String^ name = itm->sound_object->name;
		int ind = name->LastIndexOf("/");
		if(ind>0)
			name = name->Remove(0, ind+1);
		
		String^ path = root->FullPath + "/" + name;
		tree_node^ n = nullptr;
		if(itm->sound_type==sound_object_type::single)
		{
			n = m_tree_view->add_item(path, editor_base::node_sound_file);
			if ( itm->sound_object->is_exist )
				n->ForeColor			= System::Drawing::Color::Black;
			else
				n->ForeColor			= System::Drawing::Color::Red;
		}
		else
		{
			n = m_tree_view->add_group(path, editor_base::folder_closed, editor_base::folder_open);
			fill_tree_view(n, itm->sound_object->items());
		}

		n->Tag = itm;
	}
}

void sound_collection_document::undo()
{
	m_command_engine->rollback(-1);
	is_saved = m_command_engine->saved_flag();
}

void sound_collection_document::redo()
{
	m_command_engine->rollback(1);
	is_saved = m_command_engine->saved_flag();
}

void sound_collection_document::copy(bool del)
{
	VOSTOK_UNREFERENCED_PARAMETER(del);
}

void sound_collection_document::paste()
{
}

void sound_collection_document::select_all()
{
	m_tree_view->select_all();
}

void sound_collection_document::del()
{
	remove_click(nullptr, nullptr);
}

void sound_collection_document::on_document_activated(Object^, EventArgs^)
{
	if(Visible)
	{
		m_editor->clear_properties();
		on_selection_changed(nullptr, nullptr);
	}
}

void sound_collection_document::on_property_changed(Object^, value_changed_event_args^ e)
{
	List<tree_node^>^ lst = gcnew List<tree_node^>(m_tree_view->selected_nodes);
	is_saved &= !m_command_engine->run(gcnew sound_collection_change_objects_property_command(this, lst, e->changed_property->name, e->old_value, e->new_value));
}

void sound_collection_document::on_drag_over(Object^, DragEventArgs^ e)
{
	if(!e->Data->GetDataPresent("tree_view_item"))
	{
		e->Effect = DragDropEffects::None;
		return;
	}
	else
		e->Effect = DragDropEffects::Move;
}

void sound_collection_document::on_drag_drop(Object^, DragEventArgs^ e)
{
	if(m_collection==nullptr)
	{
		e->Effect = DragDropEffects::None;
		MessageBox::Show(this, "Save document first, please!", "Sound editor", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if(e->Data->GetDataPresent("tree_view_item"))
	{
		tree_node_type tnt = safe_cast<tree_node_type>(e->Data->GetData("item_type"));
		if(tnt!=tree_node_type::single_item)
		{
			e->Effect = DragDropEffects::None;
			return;
		}

		System::Drawing::Point node_position = m_tree_view->PointToClient(System::Drawing::Point(e->X, e->Y));
		tree_node^ dest_node = safe_cast<tree_node^>(m_tree_view->GetNodeAt(node_position));
		List<String^>^ lst = safe_cast<List<String^>^>(e->Data->GetData("tree_view_item"));
		sound_object_type t = (sound_object_type)safe_cast<u32>(e->Data->GetData("mode"));
		for each(String^ drag_node_name in lst)
		{
			tree_node^ drag_node = m_editor->files_view->get_node(drag_node_name);
			R_ASSERT(drag_node!=nullptr);
			if(drag_node->m_node_type==tree_node_type::single_item && 
				!(m_editor->get_sound(drag_node_name, t)->is_loaded))
			{
				MessageBox::Show(this, "Sound ["+drag_node_name+"] is loading. Please, wait...", 
									"Sound editor", MessageBoxButtons::OK, MessageBoxIcon::Error);
				e->Effect = DragDropEffects::None;
				return;
			}

			TreeNodeCollection^ col;
			if(dest_node)
				col = dest_node->nodes;
			else
				col = m_tree_view->nodes;

			if(dest_node==drag_node || col->Contains(drag_node))
			{
				e->Effect = DragDropEffects::None;
				return;
			}
		}

		m_editor->add_items_to_collection(lst, dest_node, t);
	}
	else
		e->Effect = DragDropEffects::None;
}

void sound_collection_document::on_selection_changed(Object^, vostok::editor::controls::tree_view_selection_event_args^)
{
	if(m_tree_view->selected_nodes->Count==0)
		return m_editor->clear_properties();

	List<sound_object_wrapper^>^ l = gcnew List<sound_object_wrapper^>();
	for each(tree_node^ node in m_tree_view->selected_nodes)
	{
		sound_collection_item^ itm = safe_cast<sound_collection_item^>(node->Tag);
		if(itm==nullptr)
		{
			R_ASSERT(node->FullPath==m_name);
			l->Add(m_collection);
			continue;
		}

		if(itm->sound_object->is_loaded/* && !dynamic_cast<single_sound_wrapper^>(itm->sound_object)*/)
			l->Add(itm->sound_object);
	}

	array<sound_object_wrapper^>^ lst = gcnew array<sound_object_wrapper^>(l->Count);
	u32 i = 0;
	for each(sound_object_wrapper^ w in l)
		lst[i++] = w;

	if(i>0)
		m_editor->show_properties(lst, false);
	else
		m_editor->clear_properties();
}

void sound_collection_document::add_items_to_collection(List<String^>^ names_list, tree_node^ dest_node, sound_object_type t)
{
	tree_node^ root = dest_node;
	if(root==nullptr)
		root = safe_cast<tree_node^>(m_tree_view->nodes[0]);

	is_saved &= !m_command_engine->run(gcnew sound_collection_add_items_command(this, root->FullPath, names_list, t));
}

void sound_collection_document::add_item_to_collection(tree_node^ dest, sound_collection_item^ item)
{
	sound_object_wrapper^ w = nullptr;
	if(dest->Tag==nullptr)
		w = m_collection;
	else
	{
		sound_collection_item^ itm = safe_cast<sound_collection_item^>(dest->Tag);
		w = itm->sound_object;
	}

	w->add_item(item);
	items_list^ lst = gcnew items_list();
	lst->Add(item);
	fill_tree_view(dest, lst);
}

tree_node^ sound_collection_document::get_node_by_tag(TreeNodeCollection^ root, sound_collection_item^ tag)
{
	tree_node^ res = nullptr;
	for each(tree_node^ n in root)
	{
		if(n->Tag==tag)
			return n;

		if(n->nodes->Count>0)
			res = get_node_by_tag(n->nodes, tag);

		if(res!=nullptr)
			return res;
	}

	return nullptr;
}

void sound_collection_document::remove_item_from_collection(sound_collection_item^ item)
{
	tree_node^ n = get_node_by_tag(m_tree_view->nodes, item);
	R_ASSERT(n!=nullptr);
	tree_node^ p = safe_cast<tree_node^>(n->Parent);
	R_ASSERT(p!=nullptr);
	m_tree_view->remove_item(n->FullPath);
	sound_object_wrapper^ w = m_collection;
	if(p->Tag!=nullptr)
		w = safe_cast<sound_collection_item^>(p->Tag)->sound_object;

	w->remove_item(item);
	delete item;
}

void sound_collection_document::menu_opened(Object^, EventArgs^)
{
	addCollectionToolStripMenuItem->Visible = true;
	removeToolStripMenuItem->Visible = true;
	if(m_tree_view->selected_nodes->Count==0)
		removeToolStripMenuItem->Visible = false;
	else
	{
		if(m_tree_view->selected_nodes[0]->m_node_type==tree_node_type::single_item)
			addCollectionToolStripMenuItem->Visible = false;
	}
}

void sound_collection_document::remove_click(Object^, EventArgs^)
{
	if(m_tree_view->selected_nodes->Count==0)
		return;

	List<tree_node^>^ items_list = gcnew List<tree_node^>(m_tree_view->selected_nodes);
	is_saved &= !m_command_engine->run(gcnew sound_collection_remove_items_command(this, items_list));
}

void sound_collection_document::add_collection_click(Object^, EventArgs^)
{
	if(m_collection==nullptr)
	{
		MessageBox::Show(this, "Save document first, please!", "Sound editor", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	tree_node^ n = safe_cast<tree_node^>(m_tree_view->nodes[0]);
	if(m_tree_view->selected_nodes->Count!=0)
		n = m_tree_view->selected_nodes[0];

	is_saved &= !m_command_engine->run(gcnew sound_collection_create_collection_command(this, n->FullPath));
}