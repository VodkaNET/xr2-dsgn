////////////////////////////////////////////////////////////////////////////
//	Created		: 18.11.2011
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_PATROL_GRAPH_DELETE_PART_ACTION_H_INCLUDED
#define OBJECT_PATROL_GRAPH_DELETE_PART_ACTION_H_INCLUDED

#include "object_patrol_graph_action.h"

using namespace System;

namespace vostok
{
	namespace editor
	{
		ref class object_patrol_graph;

		ref class object_patrol_graph_delete_part_action: object_patrol_graph_action
		{
		public:
			object_patrol_graph_delete_part_action			( String^ name, editor_base::scene_view_panel^ value );

		private:
			editor_base::scene_view_panel^	m_window_view;

		public:
			virtual bool		do_it						( ) override;

		private:
			typedef object_patrol_graph_action	super;

		}; // class object_patrol_graph_delete_part_action

	} // namespace editor
} // namespace vostok

#endif // #ifndef OBJECT_PATROL_GRAPH_DELETE_PART_ACTION_H_INCLUDED