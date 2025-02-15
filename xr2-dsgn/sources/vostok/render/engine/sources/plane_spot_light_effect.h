////////////////////////////////////////////////////////////////////////////
//	Created		: 21.04.2011
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef PLANE_SPOT_LIGHT_EFFECT_H_INCLUDED
#define PLANE_SPOT_LIGHT_EFFECT_H_INCLUDED

#include <vostok/render/core/effect_descriptor.h>
#include <vostok/render/core/effect_compiler.h>
#include "shared_names.h"

namespace vostok {
namespace render {

template < bool shadowed >
class plane_spot_light_effect : public effect_descriptor {
private:
	virtual	void compile	( effect_compiler& compiler, custom_config_value const& config )
	{
		VOSTOK_UNREFERENCED_PARAMETER			( config );

		shader_configuration configuration;
		configuration.shadowed_light		= shadowed;
		
		compiler.begin_technique(); // front side of plane_spot
			compiler.begin_pass	( "light", NULL, "plane_spot_light_accumulator", configuration, NULL);
				compiler.set_depth			( true, false, D3D_COMPARISON_LESS_EQUAL);
				//compiler.set_stencil		( true, 0x81, 0x81, 0xff, D3D_COMPARISON_EQUAL, D3D_STENCIL_OP_KEEP, D3D_STENCIL_OP_DECR, D3D_STENCIL_OP_DECR);
				compiler.set_stencil		( true, 0xff, check_all_geometry_type, 0xff, D3D_COMPARISON_EQUAL, D3D_STENCIL_OP_KEEP, D3D_STENCIL_OP_INVERT, D3D_STENCIL_OP_INVERT);
				compiler.set_alpha_blend	( true, D3D_BLEND_ONE, D3D_BLEND_ONE, D3D_BLEND_OP_ADD, D3D_BLEND_ONE, D3D_BLEND_ONE, D3D_BLEND_OP_ADD);
				compiler.set_cull_mode		( D3D_CULL_BACK);
				compiler.set_texture		( "t_position",    r2_rt_p);
				compiler.set_texture		( "t_normal",      r2_rt_n);
				compiler.set_texture		( "t_material",    r2_material);
				compiler.set_texture		( "t_target_ex",   r2_rt_p_ex);
				compiler.set_texture		( "t_emissive",    r2_rt_emissive);
				compiler.set_texture		( "t_decals_diffuse", r2_rt_decals_diffuse);
				compiler.set_texture		( "t_decals_normal", r2_rt_decals_normal);

				compiler.set_texture		( "t_tangents", r2_rt_tangents);
				//compiler.set_texture		( "shadowmap_texture", r2_rt_shadow_map);
			compiler.end_pass();
		compiler.end_technique();
		
		compiler.begin_technique(); // back side of plane_spot
			compiler.begin_pass	( "light", NULL, "plane_spot_light_accumulator", configuration, NULL);
				compiler.set_depth			( false, false, D3D_COMPARISON_LESS_EQUAL);
				//compiler.set_stencil		( true, 0x81, 0x81, 0xff, D3D_COMPARISON_EQUAL, D3D_STENCIL_OP_KEEP, D3D_STENCIL_OP_DECR, D3D_STENCIL_OP_KEEP);
				compiler.set_stencil		( true, 0xff, check_all_geometry_type, 0xff, D3D_COMPARISON_EQUAL, D3D_STENCIL_OP_KEEP, D3D_STENCIL_OP_INVERT, D3D_STENCIL_OP_KEEP);
				compiler.set_alpha_blend	( true, D3D_BLEND_ONE, D3D_BLEND_ONE, D3D_BLEND_OP_ADD, D3D_BLEND_ONE, D3D_BLEND_ONE, D3D_BLEND_OP_ADD);
				compiler.set_cull_mode		( D3D_CULL_FRONT);
				compiler.set_texture		( "t_position",    r2_rt_p);
				compiler.set_texture		( "t_normal",      r2_rt_n);
				compiler.set_texture		( "t_material",    r2_material);
				compiler.set_texture		( "t_target_ex",   r2_rt_p_ex);
				compiler.set_texture		( "t_emissive",    r2_rt_emissive);
				compiler.set_texture		( "t_decals_diffuse", r2_rt_decals_diffuse);
				compiler.set_texture		( "t_decals_normal", r2_rt_decals_normal);

				compiler.set_texture		( "t_tangents", r2_rt_tangents);
				//compiler.set_texture		( "shadowmap_texture", r2_rt_shadow_map);
			compiler.end_pass();
		compiler.end_technique();
	}
}; // class plane_spot_light_effect

} // namespace render
} // namespace vostok

#endif // #ifndef PLANE_SPOT_LIGHT_EFFECT_H_INCLUDED