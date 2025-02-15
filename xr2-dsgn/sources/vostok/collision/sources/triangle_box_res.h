////////////////////////////////////////////////////////////////////////////
//	Created		: 10.03.2009
//	Author		: Konstantin Slipchenko
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef TRIANGLE_BOX_RES_H_INCLUDED
#define TRIANGLE_BOX_RES_H_INCLUDED
#include "triangle_mesh_primitiv_res.h"
namespace vostok {
namespace collision {
struct on_contact;
namespace detail{
struct triangle_box_res: 
public triangle_mesh_primitiv_res
{

	triangle_box_res( u32 _local_id, const u32 *ind ): triangle_mesh_primitiv_res( _local_id, ind ){}

}; // class triangle_box_res
}// vostok
}// collision
}// detail
#endif // #ifndef TRIANGLE_BOX_RES_H_INCLUDED