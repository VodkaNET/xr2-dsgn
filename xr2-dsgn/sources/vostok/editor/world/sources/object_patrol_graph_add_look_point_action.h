////////////////////////////////////////////////////////////////////////////
//	Created		: 02.12.2011
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_PATROL_GRAPH_ADD_LOOK_POINT_ACTION_H_INCLUDED
#define OBJECT_PATROL_GRAPH_ADD_LOOK_POINT_ACTION_H_INCLUDED

#include "object_patrol_graph_action.h"

namespace vostok
{
	namespace editor
	{
		ref class object_patrol_graph_add_look_point_action: object_patrol_graph_action
		{
			typedef object_patrol_graph_action	super;
		public:

			object_patrol_graph_add_look_point_action		( String^ name, editor_base::scene_view_panel^ v );

		private:
			editor_base::scene_view_panel^	m_window_view;

		public:
			virtual bool		do_it						( ) override;

		}; // class object_patrol_graph_add_look_point_action

	} // namespace editor
} // namespace vostok

#endif // #ifndef OBJECT_PATROL_GRAPH_ADD_LOOK_POINT_ACTION_H_INCLUDED