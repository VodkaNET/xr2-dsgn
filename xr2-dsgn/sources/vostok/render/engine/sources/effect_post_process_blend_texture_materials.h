////////////////////////////////////////////////////////////////////////////
//	Created		: 13.12.2010
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef EFFECT_POST_PROCESS_BLEND_TEXTURE_MATERIALS_H_INCLUDED
#define EFFECT_POST_PROCESS_BLEND_TEXTURE_MATERIALS_H_INCLUDED

#include <vostok/render/core/effect_descriptor.h>

namespace vostok {
namespace render {

class effect_post_process_blend_texture_materials: public effect_descriptor
{
public:
	virtual void compile( effect_compiler& compiler, const custom_config_value& custom_config);
	
}; // class effect_post_process_blend_texture_materials

} // namespace render 
} // namespace vostok 


#endif // #ifndef EFFECT_POST_PROCESS_BLEND_TEXTURE_MATERIALS_H_INCLUDED