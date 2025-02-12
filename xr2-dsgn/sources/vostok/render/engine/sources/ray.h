////////////////////////////////////////////////////////////////////////////
//	Created		: 25.11.2010
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_ENGINE_RAY_H_INCLUDED
#define VOSTOK_RENDER_ENGINE_RAY_H_INCLUDED

namespace vostok {
namespace render {

struct ray
{
	ray( ) { }
	ray( float3 const& position, float3 const& direction ):	origin(position), direction(direction) { }

	float3 direction;
	float3 origin;

}; // class ray


} // namespace render
} // namespace vostok

#endif // #ifndef VOSTOK_RENDER_ENGINE_RAY_H_INCLUDED