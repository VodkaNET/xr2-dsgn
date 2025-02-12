////////////////////////////////////////////////////////////////////////////
//	Created		: 20.07.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_PARTICLE_ENGINE_H_INCLUDED
#define VOSTOK_PARTICLE_ENGINE_H_INCLUDED

#include <vostok/particle/particle_data_type.h>
#include <vostok/particle/base_particle.h>

namespace vostok {
namespace particle {

class particle_emitter_instance;
struct render_particle_emitter_instance;

struct VOSTOK_NOVTABLE engine {
	virtual	render_particle_emitter_instance*	create_render_emitter_instance	(
													particle_emitter_instance& particle_emitter_instance,
													particle_list_type const& particle_list,
													billboard_parameters* billboard_parameters,
													beamtrail_parameters* beamtrail_parameters,
													enum_particle_locked_axis locked_axis,
													enum_particle_screen_alignment screen_alignment,
													math::float4x4 const& transform,
													math::float4 const& instance_color
												) = 0;
	virtual	void								destroy							( render_particle_emitter_instance*& instance ) = 0;

protected:
	VOSTOK_DECLARE_PURE_VIRTUAL_DESTRUCTOR( engine )
}; // class engine

} // namespace particle
} // namespace vostok

#endif // #ifndef VOSTOK_PARTICLE_ENGINE_H_INCLUDED