////////////////////////////////////////////////////////////////////////////
//	Created		: 21.04.2011
//	Author		: Dmitry Kulikov
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef SPL_UTILS_H_INCLUDED
#define SPL_UTILS_H_INCLUDED

#include <vostok/math_curve.h>

namespace vostok {
namespace sound {

#ifndef MASTER_GOLD

typedef configs::binary_config_ptr spl_ptr;

configs::lua_config_ptr create_default_spl_config	( fs_new::virtual_path_string file_name );

//void					create_default_spl_config	(	fs_new::virtual_path_string file_name,
//														memory::base_allocator* allocator
//													);

VOSTOK_SOUND_API configs::lua_config_ptr	create_default_spl_config	(	fs_new::virtual_path_string file_name,
														memory::base_allocator* allocator
													);


#endif // #ifndef MASTER_GOLD

} // namespace sound
} // namespace vostok

#endif // #ifndef SPL_UTILS_H_INCLUDED