////////////////////////////////////////////////////////////////////////////
//	Created 	: 18.11.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_DRAW_TRIANGLES_COMMAND_INLINE_H_INCLUDED
#define DEBUG_DRAW_TRIANGLES_COMMAND_INLINE_H_INCLUDED

namespace vostok {
namespace render {
namespace debug {

inline draw_triangles_command::draw_triangles_command	(
		scene_ptr const& scene,
		engine::world& renderer,
		vertices_type const& vertices,
		indices_type const& indices,
		bool use_depth
	) :
	super		( true, use_depth ),
	m_scene		( scene ),
	m_renderer	( renderer ),
	m_vertices	( vertices ),
	m_indices	( indices )
{
	ASSERT		( m_indices.size( ) >= m_vertices.size( ) );
}

template < int vertex_count, int index_count >
inline draw_triangles_command::draw_triangles_command	(
		scene_ptr const& scene,
		engine::world& renderer,
		memory::base_allocator& allocator,
		vertex_colored const ( &vertices )[ vertex_count ],
		u16 const ( &indices )[ index_count ],
		bool use_depth
	) :
	super		( true, use_depth ),
	m_scene		( scene ),
	m_renderer	( renderer ),
	m_vertices	( allocator, &vertices[0], &vertices[0] + vertex_count ),
	m_indices	( allocator, &indices[0], &indices[0] + index_count )
{
	COMPILE_ASSERT( index_count >= vertex_count, please_remove_redundant_vertices );
}

template < template < typename T > class container_type >
inline draw_triangles_command::draw_triangles_command	(
		scene_ptr const& scene,
		engine::world& renderer,
		memory::base_allocator& allocator,
		container_type < vertex_colored > const& vertices,
		container_type < u16 > const& indices,
		bool use_depth
	) :
	super		( true, use_depth ),
	m_scene		( scene ),
	m_renderer	( renderer ),
	m_vertices	( allocator, vertices.begin( ), vertices.end( ) ),
	m_indices	( allocator, indices.begin( ), indices.end( ) )
{
}

} // namespace debug
} // namespace render
} // namespace vostok

#endif // #ifndef DEBUG_DRAW_TRIANGLES_COMMAND_INLINE_H_INCLUDED