////////////////////////////////////////////////////////////////////////////
//	Created		: 04.08.2011
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "composite_sound_commands.h"
#include "composite_sound_document.h"
#include "sound_object_wrapper.h"
#include "composite_sound_wrapper.h"
#include "single_sound_wrapper.h"
#include "composite_sound_item.h"
#include <vostok/strings_stream.h>

using vostok::sound_editor::composite_sound_add_items_command;
using vostok::sound_editor::composite_sound_remove_items_command;
using vostok::sound_editor::composite_sound_change_objects_property_command;
using vostok::sound_editor::composite_sound_create_collection_command;
using vostok::sound_editor::composite_sound_document;
using vostok::sound_editor::sound_object_type;
using vostok::editor::controls::tree_node;
////////////////////////////////////////////////////////////////////////////
// public ref class composite_sound_add_items_command //////////////////////
////////////////////////////////////////////////////////////////////////////
composite_sound_add_items_command::composite_sound_add_items_command(composite_sound_document^ d, String^ root_path, List<String^>^ names_list, sound_object_type t)
:m_document(d),
m_root_path(root_path)
{
	vostok::configs::lua_config_ptr cfg = vostok::configs::create_lua_config();
	vostok::strings::stream stream(g_allocator);
	vostok::configs::lua_config_value root = cfg->get_root()["items"];
	for(int i=0; i<names_list->Count; ++i)
	{
		root[i]["playing_offset"] = 0;
		unmanaged_string name(names_list[i]);
		root[i]["filename"] = name.c_str();
		if(t==sound_object_type::single)
			root[i]["resource_type"] = resources::single_sound_class;
		else if(t==sound_object_type::composite)
			root[i]["resource_type"] = resources::composite_sound_class;
		else
			root[i]["resource_type"] = resources::sound_collection_class;
	}

	cfg->save(stream);
	stream.append("%c", 0);
	m_cfg_string = strings::duplicate(g_allocator, (pcstr)stream.get_buffer());
}

composite_sound_add_items_command::~composite_sound_add_items_command()
{
	FREE(m_cfg_string);
}

bool composite_sound_add_items_command::commit()
{
	vostok::editor::controls::tree_node^ dest = m_document->get_tree_view()->get_node(m_root_path);
	R_ASSERT(dest!=nullptr);
	vostok::configs::lua_config_ptr config_ptr = vostok::configs::create_lua_config_from_string(m_cfg_string);
	if(!config_ptr || config_ptr->empty()) 
		return false;

	vostok::configs::lua_config_iterator it = config_ptr->get_root()["items"].begin();
	for(; it!=config_ptr->get_root()["items"].end(); ++it)
	{
		composite_sound_item^ item = gcnew composite_sound_item();
		item->load(*it);
		m_document->add_item_to_collection(dest, item);
	}

	return true;
}

void composite_sound_add_items_command::rollback()
{
	vostok::editor::controls::tree_node^ dest = m_document->get_tree_view()->get_node(m_root_path);
	R_ASSERT(dest!=nullptr);
	sound_object_wrapper^ w = nullptr;
	if(dest->Tag==nullptr)
		w = m_document->get_sound();
	else
		w = safe_cast<composite_sound_item^>(dest->Tag)->sound_object;

	R_ASSERT(w->items()!=nullptr);
	vostok::configs::lua_config_ptr config_ptr = vostok::configs::create_lua_config_from_string(m_cfg_string);
	if(!config_ptr || config_ptr->empty()) 
		return;

	vostok::configs::lua_config_iterator it = config_ptr->get_root()["items"].begin();
	for(; it!=config_ptr->get_root()["items"].end(); ++it)
	{
		String^ name = gcnew String((*it)["filename"]);
		for each(composite_sound_item^ item in w->items())
		{
			if(item->ToString()==name)
			{
				m_document->remove_item_from_collection(item);
				break;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////
// public ref class composite_sound_remove_items_command ///////////////////
////////////////////////////////////////////////////////////////////////////
composite_sound_remove_items_command::composite_sound_remove_items_command(composite_sound_document^ d, List<tree_node^>^ items_list)
:m_document(d)
{
	m_saved_nodes = gcnew List<tree_node^>();
	vostok::configs::lua_config_ptr cfg = vostok::configs::create_lua_config();
	vostok::strings::stream stream(g_allocator);
	vostok::configs::lua_config_value root = cfg->get_root()["items"];
	for(int i=0; i<items_list->Count; ++i)
	{
		vostok::configs::lua_config_value val = root[i];
		save_childs(items_list[i], val);
	}

	delete m_saved_nodes;
	cfg->save(stream);
	stream.append("%c", 0);
	m_cfg_string = strings::duplicate(g_allocator, (pcstr)stream.get_buffer());
}

composite_sound_remove_items_command::~composite_sound_remove_items_command()
{	
	FREE(m_cfg_string);
}

void composite_sound_remove_items_command::save_childs(tree_node^ n, vostok::configs::lua_config_value& root)
{
	if(m_saved_nodes->Contains(n))
		return;

	if(n->Tag==nullptr)
		return;

	m_saved_nodes->Add(n);
	composite_sound_item^ item = safe_cast<composite_sound_item^>(n->Tag);
	unmanaged_string name(item->ToString());
	root["filename"] = name.c_str();
	unmanaged_string full_path(n->Parent->FullPath);
	root["full_path"] = full_path.c_str();
	if(item->sound_type==sound_object_type::single)
		root["resource_type"] = resources::single_sound_class;
	else if(item->sound_type==sound_object_type::composite)
		root["resource_type"] = resources::composite_sound_class;
	else
		root["resource_type"] = resources::sound_collection_class;

	for(int i=0; i<n->nodes->Count; ++i)
	{
		vostok::configs::lua_config_value val = root["items"][i];
		save_childs(safe_cast<tree_node^>(n->nodes[i]), val);
	}
}

void composite_sound_remove_items_command::remove_childs(vostok::configs::lua_config_value& root)
{
	if(root.value_exists("items"))
	{
		vostok::configs::lua_config_iterator it = root["items"].begin();
		for(; it!=root["items"].end(); ++it)
		{
			vostok::configs::lua_config_value val = *it;
			remove_childs(val);
		}
	}

	String^ filename = gcnew String((pcstr)root["filename"]);
	String^ full_path = gcnew String((pcstr)root["full_path"]);
	vostok::editor::controls::tree_node^ parent = m_document->get_tree_view()->get_node(full_path);
	sound_object_wrapper^ w = nullptr;
	if(parent->Tag!=nullptr)
		w = safe_cast<composite_sound_item^>(parent->Tag)->sound_object;
	else
		w = m_document->get_sound();

	composite_sound_item^ item = nullptr;
	for each(composite_sound_item^ itm in w->items())
	{
		if(itm->ToString()==filename)
		{
			item = itm;
			break;
		}
	}
	
	m_document->remove_item_from_collection(item);
}

bool composite_sound_remove_items_command::commit()
{
	vostok::configs::lua_config_ptr config_ptr = vostok::configs::create_lua_config_from_string(m_cfg_string);
	if(!config_ptr || config_ptr->empty()) 
		return false;

	vostok::configs::lua_config_iterator it = config_ptr->get_root()["items"].begin();
	for(; it!=config_ptr->get_root()["items"].end(); ++it)
	{
		vostok::configs::lua_config_value val = *it;
		remove_childs(val);
	}

	return true;
}

void composite_sound_remove_items_command::add_childs(vostok::configs::lua_config_value& root)
{
	composite_sound_item^ item = gcnew composite_sound_item();
	item->load(root);
	String^ full_path = gcnew String((pcstr)root["full_path"]);
	vostok::editor::controls::tree_node^ dest = m_document->get_tree_view()->get_node(full_path);
	R_ASSERT(dest!=nullptr);
	m_document->add_item_to_collection(dest, item);
}

void composite_sound_remove_items_command::rollback()
{
	vostok::configs::lua_config_ptr config_ptr = vostok::configs::create_lua_config_from_string(m_cfg_string);
	if(!config_ptr || config_ptr->empty()) 
		return;

	vostok::configs::lua_config_iterator it = config_ptr->get_root()["items"].begin();
	for(; it!=config_ptr->get_root()["items"].end(); ++it)
	{
		vostok::configs::lua_config_value val = *it;
		add_childs(val);
	}
}
////////////////////////////////////////////////////////////////////////////
// public ref class sound_collection_change_objects_property_command ///////
////////////////////////////////////////////////////////////////////////////
composite_sound_change_objects_property_command::composite_sound_change_objects_property_command(composite_sound_document^ d, List<tree_node^>^ obj_list, String^ prop_name, Object^ old_val, Object^ new_val)
:m_document(d),
m_property_name(prop_name),
m_old_val(old_val),
m_new_val(new_val)
{
	m_nodes_paths = gcnew paths_list();
	for each(tree_node^ n in obj_list)
		m_nodes_paths->Add(n->FullPath);
}

composite_sound_change_objects_property_command::~composite_sound_change_objects_property_command()
{
	delete m_nodes_paths;
}

bool composite_sound_change_objects_property_command::commit()
{
	for(int i=0; i<m_nodes_paths->Count; ++i)
	{
		tree_node^ n = m_document->get_tree_view()->get_node(m_nodes_paths[i]);
		sound_object_wrapper^ w = nullptr;
		composite_sound_item^ itm = nullptr;
		if(n->Tag==nullptr)
			w = m_document->get_sound();
		else
			itm = safe_cast<composite_sound_item^>(n->Tag);

		System::Reflection::PropertyInfo^ inf = nullptr;
		if(w!=nullptr)
		{
			inf = w->GetType()->GetProperty(m_property_name);
			if(inf!=nullptr)
				inf->SetValue(w, m_new_val, nullptr);
		}
		else
		{
			inf = itm->GetType()->GetProperty(m_property_name);
			if(inf!=nullptr)
				inf->SetValue(itm, m_new_val, nullptr);
		}
	}

	return true;
}

void composite_sound_change_objects_property_command::rollback()
{
	for(int i=0; i<m_nodes_paths->Count; ++i)
	{
		tree_node^ n = m_document->get_tree_view()->get_node(m_nodes_paths[i]);
		sound_object_wrapper^ w = nullptr;
		composite_sound_item^ itm = nullptr;
		if(n->Tag==nullptr)
			w = m_document->get_sound();
		else
			itm = safe_cast<composite_sound_item^>(n->Tag);

		System::Reflection::PropertyInfo^ inf = nullptr;
		if(w!=nullptr)
		{
			inf = w->GetType()->GetProperty(m_property_name);
			if(inf!=nullptr)
				inf->SetValue(w, m_old_val, nullptr);
		}
		else
		{
			inf = itm->GetType()->GetProperty(m_property_name);
			if(inf!=nullptr)
				inf->SetValue(itm, m_old_val, nullptr);
		}
	}
}
////////////////////////////////////////////////////////////////////////////
// public ref class composite_sound_create_collection_command //////////////
////////////////////////////////////////////////////////////////////////////
composite_sound_create_collection_command::composite_sound_create_collection_command(composite_sound_document^ d, String^ root_path)
:m_document(d),
m_root_path(root_path)
{
	m_id = System::Guid::NewGuid().ToString();
	vostok::configs::lua_config_ptr cfg = vostok::configs::create_lua_config();
	vostok::strings::stream stream(g_allocator);
	vostok::configs::lua_config_value root = cfg->get_root()["collection"];
	root["cyclic_repeat_from_sound"] = 0;
	root["dont_repeat_sound_successively"] = false;
	root["max_delay"] = 0;
	root["min_delay"] = 0;
	root["type"] = "random";
	cfg->save(stream);
	stream.append("%c", 0);
	m_cfg_string = strings::duplicate(g_allocator, (pcstr)stream.get_buffer());
}

composite_sound_create_collection_command::~composite_sound_create_collection_command()
{
	FREE(m_cfg_string);
}

bool composite_sound_create_collection_command::commit()
{
	vostok::configs::lua_config_ptr config_ptr = vostok::configs::create_lua_config_from_string(m_cfg_string);
	if(!config_ptr || config_ptr->empty()) 
		return false;

	composite_sound_wrapper^ w = gcnew composite_sound_wrapper(m_id);
	w->load(config_ptr->get_root());
	vostok::editor::controls::tree_node^ dest = m_document->get_tree_view()->get_node(m_root_path);
	R_ASSERT(dest!=nullptr);
	composite_sound_item^ itm = gcnew composite_sound_item();
	itm->sound_object = w;
	itm->sound_type = sound_object_type::collection;
	itm->is_link = false;
	m_document->add_item_to_collection(dest, itm);
	return true;
}

void composite_sound_create_collection_command::rollback()
{
	vostok::editor::controls::tree_node^ dest = m_document->get_tree_view()->get_node(m_root_path);
	R_ASSERT(dest!=nullptr);
	sound_object_wrapper^ w = m_document->get_sound();
	if(dest->Tag!=nullptr)
		w = safe_cast<composite_sound_item^>(dest->Tag)->sound_object;

	R_ASSERT(!dynamic_cast<single_sound_wrapper^>(w));
	for each(composite_sound_item^ itm in w->items())
	{
		if(itm->ToString()==m_id)
		{
			m_document->remove_item_from_collection(itm);
			return;
		}
	}
}
