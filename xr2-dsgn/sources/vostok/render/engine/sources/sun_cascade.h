////////////////////////////////////////////////////////////////////////////
//	Created		: 25.11.2010
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_ENGINE_SUN_CASCADE_H_INCLUDED
#define VOSTOK_RENDER_ENGINE_SUN_CASCADE_H_INCLUDED

#include "ray.h"

namespace vostok {
namespace render {


struct sun_cascade 
{
	enum { num_max_sun_shadow_cascades = 4 };

	sun_cascade  () : reset_chain( false )	{}

	float4x4				transform;
	fixed_vector<ray, 8>	rays;
	float					size;
	float					bias;
	bool					reset_chain;
};

} // namespace render
} // namespace vostok

#endif // #ifndef VOSTOK_RENDER_ENGINE_SUN_CASCADE_H_INCLUDED