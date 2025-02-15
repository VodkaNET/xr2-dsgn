////////////////////////////////////////////////////////////////////////////
//	Created		: 19.10.2010
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////
#ifndef ANIMATION_VIEWER_GRAPH_LINK_TIMED_H_INCLUDED
#define ANIMATION_VIEWER_GRAPH_LINK_TIMED_H_INCLUDED

#include "animation_viewer_graph_link.h"

namespace vostok {
namespace animation_editor {
	ref class animation_viewer_graph_link;
	ref class time_instance;

	public ref class animation_viewer_graph_link_timed : public animation_viewer_graph_link
	{
		typedef vostok::animation_editor::animation_viewer_graph_link		super;
		typedef vostok::editor::controls::hypergraph::connection_point	connection_point;
		typedef vostok::editor::wpf_controls::property_container			wpf_property_container;

	public:
						animation_viewer_graph_link_timed	(connection_point^ src, connection_point^ dst);
						~animation_viewer_graph_link_timed	();

		virtual	void	load								(vostok::configs::lua_config_value const& cfg) override;
		virtual	void	save								(vostok::configs::lua_config_value cfg) override;
		virtual	void	draw								(System::Drawing::Graphics^ g, System::Drawing::Pen^ pen, vostok::editor::controls::hypergraph::nodes_link_style link_style) override;

		[CategoryAttribute("Link properties"), DisplayNameAttribute("playing_time")]
		property wpf_property_container^	playing_time
		{
			wpf_property_container^			get				();
			void							set				(wpf_property_container^) {};
		}

	private:
		time_instance^ m_time;
	}; // ref class animation_viewer_graph_link_timed
} // namespace animation_editor
} // namespace vostok
#endif // #ifndef ANIMATION_VIEWER_GRAPH_LINK_TIMED_H_INCLUDED