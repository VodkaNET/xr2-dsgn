////////////////////////////////////////////////////////////////////////////
//	Created		: 02.12.2010
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef EFFECT_FSTAGE_DEFAULT_MATERIALS_H_INCLUDED
#define EFFECT_FSTAGE_DEFAULT_MATERIALS_H_INCLUDED

#include "effect_material_base.h"

namespace vostok {
namespace render {

class effect_fstage_default_materials: public effect_material_base
{
public:
	effect_fstage_default_materials() {}
	
	virtual	void compile(effect_compiler& compiler, custom_config_value const& config);

}; // class effect_fstage_default_materials

} // namespace render 
} // namespace vostok 


#endif // #ifndef EFFECT_FSTAGE_DEFAULT_MATERIALS_H_INCLUDED
