////////////////////////////////////////////////////////////////////////////
//	Created		: 04.02.2010
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef STAGE_PRE_LIGHTING_H_INCLUDED
#define STAGE_PRE_LIGHTING_H_INCLUDED

#include "stage.h"

namespace vostok {
namespace render {

class stage_pre_lighting: public stage
{
public:
	stage_pre_lighting	( renderer_context* context): stage( context){}

	virtual void execute( );

}; // class stage_pre_lighting

} // namespace render
} // namespace vostok

#endif // #ifndef STAGE_PRE_LIGHTING_H_INCLUDED