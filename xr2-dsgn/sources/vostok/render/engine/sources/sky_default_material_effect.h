////////////////////////////////////////////////////////////////////////////
//	Created		: 22.09.2011
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_SKY_DEFAULT_MATERIAL_EFFECT_H_INCLUDED
#define VOSTOK_RENDER_SKY_DEFAULT_MATERIAL_EFFECT_H_INCLUDED

#include "effect_material_base.h"

namespace vostok {
namespace render {

class sky_default_material_effect: public effect_material_base
{
public:
	virtual void compile( effect_compiler& compiler, const custom_config_value& custom_config);
}; // class sky_default_material_effect

} // namespace render 
} // namespace vostok 


#endif // #ifndef VOSTOK_RENDER_SKY_DEFAULT_MATERIAL_EFFECT_H_INCLUDED