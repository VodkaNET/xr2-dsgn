////////////////////////////////////////////////////////////////////////////
//	Created		: 27.10.2011
//	Author		: Tetyana Meleshchenko
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <vostok/ai/animation_item.h>

namespace vostok {
namespace ai {

animation_item::animation_item	( resources::unmanaged_resource_ptr const& new_item, pcstr filename ) :
	animation					( new_item ),
	name						( filename )
{
}

} // namespace ai
} // namespace vostok