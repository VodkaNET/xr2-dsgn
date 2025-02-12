////////////////////////////////////////////////////////////////////////////
//	Created		: 22.12.2010
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef EFFECT_EDITOR_SELECTION_H_INCLUDED
#define EFFECT_EDITOR_SELECTION_H_INCLUDED

#include "effect_material_base.h"

namespace vostok {
namespace render {

class effect_editor_selection: public effect_material_base
{
public:
	virtual	void compile(effect_compiler& compiler, custom_config_value const& config);
}; // class effect_editor_selection

} // namespace render 
} // namespace vostok 


#endif // #ifndef EFFECT_EDITOR_SELECTION_H_INCLUDED
