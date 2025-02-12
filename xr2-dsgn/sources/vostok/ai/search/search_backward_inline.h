////////////////////////////////////////////////////////////////////////////
//	Created		: 14.07.2011
//	Author		: Tetyana Meleshchenko
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_AI_SEARCH_SEARCH_BACKWARD_INLINE_H_INCLUDED
#define VOSTOK_AI_SEARCH_SEARCH_BACKWARD_INLINE_H_INCLUDED

namespace vostok {
namespace ai {
namespace planning {

#define THE_SEARCH					planning::search_backward

inline THE_SEARCH::search_backward	( search_base& search ) :
	m_search						( search ),
	m_graph_wrapper					( 0 )
{
}

inline bool	THE_SEARCH::search		( propositional_planner& graph, path_type& path )
{
	m_graph_wrapper.graph			( graph );
	path_constructor_type path_constructor( &path );
	path_heuristics_type heuristics	( graph );

	R_ASSERT						( (int)search_base::max_vertex_count() > ( graph.operators().objects().size() - 1 ), "search is out of bounds" );
	search_restrictor_type restrictor(
		m_graph_wrapper,
		graph.target(),
		search_base::vertex_id_type(),
		std::numeric_limits< distance_type >::max(),
		u32(-1),
		search_base::max_vertex_count() - (u32)graph.operators().objects().size() - 1
	);

	return							(
		algorithm_type::find		(
			m_search.m_priority_queue,
			m_graph_wrapper,
			path_constructor,
			heuristics,
			restrictor
		)
	);
}

#undef THE_SEARCH

} // namespace planning
} // namespace ai
} // namespace vostok

#endif // #ifndef VOSTOK_AI_SEARCH_SEARCH_BACKWARD_INLINE_H_INCLUDED