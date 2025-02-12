////////////////////////////////////////////////////////////////////////////
//	Created		: 01.02.2010
//	Author		: Konstantin Slipchenko
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_ANIMATION_TYPE_DEFINITIONS_H_INCLUDED
#define VOSTOK_ANIMATION_TYPE_DEFINITIONS_H_INCLUDED

namespace vostok {
namespace animation {

typedef	u32									bone_index_type;
typedef	FILE*								stream;
typedef	resources::managed_resource_ptr		skeleton_animation_ptr;

enum animation_types_enum {
	animation_type_full,
	animation_type_additive,
}; // enum animation_types_enum

}  // namespace animation
}  // namespace vostok

#endif // #ifndef VOSTOK_ANIMATION_TYPE_DEFINITIONS_H_INCLUDED