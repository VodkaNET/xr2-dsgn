////////////////////////////////////////////////////////////////////////////
//	Created		: 27.07.2011
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_ENGINE_GEOMETRY_TYPE_H_INCLUDED
#define VOSTOK_RENDER_ENGINE_GEOMETRY_TYPE_H_INCLUDED

#include <vostok/render/core/effect_descriptor.h>
#include <vostok/render/core/effect_compiler.h>
#include "shared_names.h"

namespace vostok {
namespace render {

enum enum_geometry_type
{
	// static types
	terrain_geometry_type		= 1,
	static_geometry_type,
	speedtree_geometry_type,
	
	// dynamic types
	skeleton_geometry_type,
	particle_geometry_type,
	
	num_geometry_types			= 5,
	
	all_geometry_type			= 0x80,
	check_all_geometry_type		= 0x40,
	
}; // enum enum_geometry_type

} // namespace render
} // namespace vostok

#endif // #ifndef VOSTOK_RENDER_ENGINE_GEOMETRY_TYPE_H_INCLUDED