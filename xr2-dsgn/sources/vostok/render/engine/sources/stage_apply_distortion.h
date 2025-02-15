////////////////////////////////////////////////////////////////////////////
//	Created		: 01.12.2010
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef STAGE_APPLY_DISTORTION_H_INCLUDED
#define STAGE_APPLY_DISTORTION_H_INCLUDED

#include "stage.h"

namespace vostok {
namespace render {

class res_effect;
class resource_intrusive_base;
typedef	vostok::resources::resource_ptr < vostok::render::res_effect, vostok::resources::unmanaged_intrusive_base > ref_effect;

class stage_apply_distortion: public stage
{
public:
					stage_apply_distortion		(renderer_context* context);
					~stage_apply_distortion		();
	virtual void	execute						();
			bool	is_effects_ready			() const;
private:
	ref_effect		m_sh_apply_distortion;
}; // class stage_apply_distortion

} // namespace render
} // namespace vostok
#endif // #ifndef STAGE_APPLY_DISTORTION_H_INCLUDED