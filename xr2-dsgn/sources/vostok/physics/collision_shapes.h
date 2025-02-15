////////////////////////////////////////////////////////////////////////////
//	Created		: 09.09.2011
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef COLLISION_SHAPES_H_INCLUDED
#define COLLISION_SHAPES_H_INCLUDED

#include <vostok/physics/api.h>
#include <vostok/collision/primitives.h>

class btCollisionShape;

namespace vostok {
namespace physics {

class VOSTOK_PHYSICS_API bt_collision_shape : public resources::unmanaged_resource
{
public:
								bt_collision_shape		( btCollisionShape* sh/*, float3 const& center_offset*/ );
	virtual						~bt_collision_shape		( );

	inline btCollisionShape*	get_bt_shape			( ) const { return m_bt_shape; }
//	inline float3 const&		center_offset			( ) const { return m_center_offset; }
private:
	btCollisionShape*			m_bt_shape;
//	float3						m_center_offset;
}; // class collision_shape

typedef	resources::resource_ptr<
	bt_collision_shape,
	resources::unmanaged_intrusive_base
> bt_collision_shape_ptr;

VOSTOK_PHYSICS_API bt_collision_shape* create_primitive_shape				( memory::base_allocator& allocator, vostok::collision::primitive_type type, float3 const& dim );
VOSTOK_PHYSICS_API bt_collision_shape* create_compound_shape				( memory::base_allocator& allocator, configs::binary_config_value const& config );
VOSTOK_PHYSICS_API bt_collision_shape* create_static_triangle_mesh_shape	( memory::base_allocator& allocator, float3* vertices, u32* indices, u32 num_vertices, u32 num_indices );
VOSTOK_PHYSICS_API bt_collision_shape* create_dynamic_triangle_mesh_shape	( memory::base_allocator& allocator, float3* vertices, u32* indices, u32 num_vertices, u32 num_indices );
VOSTOK_PHYSICS_API bt_collision_shape* create_terrain_shape				( memory::base_allocator& allocator, float* heighfield, u32 rowcol, float min_height, float max_height );
VOSTOK_PHYSICS_API void				 destroy_shape						( memory::base_allocator& allocator, bt_collision_shape* shape );


} // namespace physics
} // namespace vostok

#endif // #ifndef COLLISION_SHAPES_H_INCLUDED