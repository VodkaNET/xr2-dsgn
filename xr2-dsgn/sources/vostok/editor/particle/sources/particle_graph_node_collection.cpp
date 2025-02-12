////////////////////////////////////////////////////////////////////////////
//	Created		: 27.01.2010
//	Author		: 
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "particle_graph_node.h"
#include "particle_graph_node_event.h"
#include "particle_graph_node_action.h"
#include "particle_graph_node_property.h"
#include "particle_graph_node_collection.h"
#include "particle_hypergraph.h"
#include "particle_graph_document.h"
#include "particle_links_manager.h"

using namespace System;


namespace vostok {
	namespace particle_editor {
	

particle_graph_node_collection::particle_graph_node_collection(particle_graph_node^ owner)
{
	m_owner					= owner;
	m_last_property_id		= 0;
	m_last_action_id		= 0;
	m_last_event_id			= 0;
	m_nodes_dictionary		= gcnew Collections::Generic::Dictionary<String^, particle_graph_node^>();

}

void	particle_graph_node_collection::Insert		(Int32 index , particle_graph_node^ node)
{
	R_ASSERT(m_owner->parent_hypergraph!=nullptr);



	node->size = m_owner->size;

	if(node->parent_hypergraph == nullptr){
		m_owner->parent_hypergraph->links_manager->on_node_destroyed(node);
		safe_cast<particle_hypergraph^>(m_owner->parent_hypergraph)->append_node(node);
	
	}
	if	(Count == 0)
		safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->create_link(m_owner, node);
	else if (index == 0){
		safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->destroy_link(m_owner, m_nodes_dictionary[this[0]]);
		safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->create_link(m_owner, node);		
	}

	node->parent_node = m_owner;
	
	super::Insert(index, node->id);
	
	bool need_sync_order = false;

	m_nodes_dictionary->Add(node->id, node);
	if (!(*m_owner->node_config)["children"].value_exists(unmanaged_string(node->id).c_str())){
		need_sync_order = true;
		((*m_owner->node_config)["children"][unmanaged_string(node->id).c_str()]).assign_lua_value(*node->node_config);
		m_owner->parent_document->particle_system_node_added(node, *node->properties->config);
	//	m_owner->node_config->save_as("d:/node_cfg");
	}

	node->parent_lod_name = m_owner->parent_document->lod_name;
	
	if (node->is_property_node()){
		m_last_property_id = m_last_property_id + 1;
	}
	else if (node->is_action_node()){
		m_last_action_id = m_last_action_id + 1;
	}
	else if (node->is_event_node()){
		m_last_event_id = m_last_event_id + 1;
	}
	

	if (m_owner->active_node == nullptr)
		m_owner->active_node = node;
// 
// 	if (m_owner == safe_cast<particle_hypergraph^>(m_owner->parent_hypergraph)->root_node)
// 		node->process_node_selection();
// 	else{
// 		m_owner->process_node_selection();
// 		node->process_node_selection();
// 	}

	m_owner->recalc_children_position_offsets();

	m_owner->parent_hypergraph->Invalidate(true);	

	if (need_sync_order)
	{
		//(*m_owner->node_config)["children_order"].insert(unmanaged_string(node->id).c_str(), index);
 		Int32 node_index = 0;
 		(*m_owner->node_config)["children_order"].clear();
  		for each(String^ n_id in this) {
  			(*m_owner->node_config)["children_order"][node_index++] = unmanaged_string(n_id).c_str();
 		}
	}
}

void	particle_graph_node_collection::Add			(particle_graph_node^ node)
{
	if (node->is_property_node()){
		Insert(m_last_property_id, node);
	}
	else if (node->is_action_node()){
		Insert(m_last_action_id + m_last_property_id, node);
	}
	else if (node->is_event_node()){
		Insert(m_last_event_id + m_last_action_id + m_last_property_id, node);
	}
	else
		Insert(Count, node);
}
void	particle_graph_node_collection::Remove		(particle_graph_node^ node){

	if (node->is_property_node()){
		m_last_property_id = m_last_property_id - 1;
	}
	else if (node->is_action_node()){
		m_last_action_id = m_last_action_id - 1;
	}
	else if (node->is_event_node()){
		m_last_event_id = m_last_event_id - 1;
	}
	
	node->parent_node		= nullptr;
	if (m_owner->active_node == node)
		m_owner->active_node	= nullptr;
	
	safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->destroy_link(m_owner, node);
	m_owner->parent_hypergraph->Invalidate(true);
	

	m_owner->parent_document->particle_system_node_removed(node);

	int node_index = this->IndexOf(node->id);
	super::Remove(node->id);
	m_nodes_dictionary->Remove(node->id);

	if (node_index == 0 && Count>0)
		safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->create_link(m_owner, m_nodes_dictionary[this[0]]);
		
	m_owner->recalc_children_position_offsets();

	((*m_owner->node_config)["children"]).erase(unmanaged_string(node->id).c_str());
	node_index = 0;
	(*m_owner->node_config)["children_order"].clear();
	for each(String^ n_id in this) {
		(*m_owner->node_config)["children_order"][node_index++] = unmanaged_string(n_id).c_str();
	}


	m_owner->parent_hypergraph->Invalidate(false);	
}
	
bool	particle_graph_node_collection::MoveToIndex		(particle_graph_node^ node, int index){
		int min_index = 0;
		int max_index = Count;

		if(node->is_property_node()){
			min_index = 0;
			max_index = m_last_property_id;
		}
		else if(node->is_action_node()){
			min_index = m_last_property_id;
			max_index = m_last_property_id + m_last_action_id;
		}
		else if(node->is_event_node()){
			min_index = m_last_property_id + m_last_action_id;
			max_index = m_last_property_id + m_last_action_id + m_last_event_id;
		}

		if (index >= max_index || index < min_index)
			return false;

		m_owner->parent_document->particle_system_property_order_changed(node->id, this[index]);

		int node_index = this->IndexOf(node->id);
		
		super::Remove(node->id);

		if (node_index == 0){
			safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->destroy_link(m_owner, node);
			safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->create_link(m_owner, m_nodes_dictionary[this[0]]);
		}
		else if (index == 0){
			safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->create_link(m_owner, node);
			safe_cast<particle_links_manager^>(m_owner->parent_hypergraph->links_manager)->destroy_link(m_owner, m_nodes_dictionary[this[0]]);
		}

			
		super::Insert(index, node->id);

		m_owner->recalc_children_position_offsets();

		node_index = 0;
		(*m_owner->node_config)["children_order"].clear();
		for each(String^ n_id in this) {
			(*m_owner->node_config)["children_order"][node_index++] = unmanaged_string(n_id).c_str();
		}

		m_owner->parent_hypergraph->Invalidate(true);	

		return true;
}

}//	namespace particle_editor 
}// namespace vostok 