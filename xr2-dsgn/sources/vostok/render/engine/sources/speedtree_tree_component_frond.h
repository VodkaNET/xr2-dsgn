////////////////////////////////////////////////////////////////////////////
//	Created		: 09.02.2011
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_SPEEDTREE_TREE_COMPONENT_FROND_H_INCLUDED
#define VOSTOK_RENDER_SPEEDTREE_TREE_COMPONENT_FROND_H_INCLUDED

#include "speedtree_tree.h"

namespace SpeedTree {
	struct SIndexedTriangles;
}

namespace vostok {
namespace render {

class speedtree_tree_component_frond: public speedtree_tree_component
{
public:
										speedtree_tree_component_frond		(speedtree_tree& parent);
	virtual void						set_material						(material_ptr mtl_ptr);
	virtual void						set_default_material				();
	virtual void						render								(lod_entry const*, renderer_context*);
	virtual SpeedTree::EGeometryType	get_geometry_type					() const { return SpeedTree::GEOMETRY_TYPE_FRONDS; };
	virtual enum_vertex_input_type		get_vertex_input_type				() { return vostok::render::speedtree_frond_vertex_input_type; }
			void						init_index_buffer					(SpeedTree::SIndexedTriangles const* lod, render::vector<u16>& out_indices);
}; // class speedtree_tree_component_frond

} // namespace render 
} // namespace vostok 

#endif // #ifndef VOSTOK_RENDER_SPEEDTREE_TREE_COMPONENT_FROND_H_INCLUDED