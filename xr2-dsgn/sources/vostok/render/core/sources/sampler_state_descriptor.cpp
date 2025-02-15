////////////////////////////////////////////////////////////////////////////
//	Created		: 13.04.2010
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <vostok/render/core/custom_config.h>
#include <vostok/render/core/sampler_state_descriptor.h>
#include <vostok/render/core/effect_compiler.h>

namespace vostok {
namespace render {

effect_compiler &	sampler_state_descriptor ::end_sampler ()
{
	ASSERT( m_effect_compiler);
	return m_effect_compiler->end_sampler();
}

} // namespace render 
} // namespace vostok