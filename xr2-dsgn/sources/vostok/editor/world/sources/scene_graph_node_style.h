////////////////////////////////////////////////////////////////////////////
//	Created		: 7.12.2009
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef SCENE_GRAPH_NODE_STYLE_H_INCLUDED
#define SCENE_GRAPH_NODE_STYLE_H_INCLUDED

namespace vostok {
namespace editor {
	public ref class scene_graph_node_style : public controls::hypergraph::node_style
	{
	public:
		void	load	(configs::lua_config_value const& t);
	}; // ref class scene_graph_node_style

	ref class scene_graph_nodes_style_mgr : public vostok::editor::controls::hypergraph::nodes_style_manager
	{
	private:
		typedef vostok::editor::controls::hypergraph::node		node;
		typedef vostok::editor::controls::hypergraph::node_style	node_style;

	public:
							scene_graph_nodes_style_mgr			( );
		virtual				~scene_graph_nodes_style_mgr		( );
		virtual		void	assign_style						( node^ n, System::String^ style_name );
					void	load_library						( );
					void	on_library_loaded					( vostok::resources::queries_result& data );
	private:
		configs::lua_config_ptr*		m_library_cfg;
		System::Collections::ArrayList^	m_library;
	}; // class scene_graph_nodes_style_mgr

} // namespace editor
} // namespace vostok

#endif // #ifndef SCENE_GRAPH_NODE_STYLE_H_INCLUDED