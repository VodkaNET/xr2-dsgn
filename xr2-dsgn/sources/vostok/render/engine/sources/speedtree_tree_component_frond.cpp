////////////////////////////////////////////////////////////////////////////
//	Created		: 09.02.2011
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "speedtree.h"
#include "speedtree_tree_component_frond.h"
#include "renderer_context.h"
#include "material_manager.h"
#include <vostok/render/core/res_declaration.h>
#include <vostok/render/core/res_geometry.h>
#include <vostok/render/core/res_effect.h>
#include <vostok/render/core/backend.h>
#include <vostok/render/facade/vertex_input_type.h>
#include <vostok/render/core/decl_utils.h>
#include <vostok/render/core/resource_manager.h>
#include <vostok/engine/console.h>
#include <vostok/console_command.h>
#include <vostok/console_command_processor.h>

namespace vostok {
namespace render {

const D3D_INPUT_ELEMENT_DESC layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D_INPUT_PER_VERTEX_DATA, 0 }, // pos.xyz
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D_INPUT_PER_VERTEX_DATA, 0 },	// LOD position.xyz + wind scalar mag
	{ "TEXCOORD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 28, D3D_INPUT_PER_VERTEX_DATA, 0 },	// diffuse texcoords.st + frond ripple
	{ "TEXCOORD", 2, DXGI_FORMAT_R8G8B8A8_UINT,		 0, 44, D3D_INPUT_PER_VERTEX_DATA, 0 },	// normal.xyz + amb occ
	{ "TEXCOORD", 3, DXGI_FORMAT_R8G8B8A8_UINT,		 0, 48, D3D_INPUT_PER_VERTEX_DATA, 0 },	// tangent.xyz
	{ "TEXCOORD", 4, DXGI_FORMAT_R8G8B8A8_UINT,		 0, 52, D3D_INPUT_PER_VERTEX_DATA, 0 },	// wind data.xyzw
};

struct frond_vertex
{
	float  m_afCoord[3];                                   // position
	float  m_afLodCoord[3], m_fWindScalarMag;              // texcoord0
	float  m_afDiffuseTexCoords[2], m_afFrondRipple[2];    // texcoord1
	u8     m_aucNormal[3], m_ucAmbOcc;                     // texcoord2
	u8     m_aucTangent[3], m_ucTangentPadding;            // texcoord3
	u8     m_aucWindData[4];                               // texcoord4
};

using namespace SpeedTree;

speedtree_tree_component_frond::speedtree_tree_component_frond(speedtree_tree& parent):
	speedtree_tree_component(parent) 
{
	ref_declaration decl = resource_manager::ref().create_declaration( layout );
	
	CTree& tree = parent;
	
	const SGeometry* tree_geometry  = tree.GetGeometry( );
	
	st_int32 num_lods				= tree_geometry->m_nNumFrondLods;
	const SIndexedTriangles* lods	= tree_geometry->m_pFrondLods;
	
	lod_render_info& lod_info		= parent.get_lod_render_info(SpeedTree::GEOMETRY_TYPE_FRONDS);
	lod_info.num_lods				= num_lods;
	lod_info.lods					= NEW_ARRAY(lod_entry, num_lods);
	
	render::vector<u16>				total_indices;
	render::vector<frond_vertex>	total_vertices;
	
	for (s32 lod_index=0; lod_index<num_lods; lod_index++)
	{
		const SIndexedTriangles* lod = lods + lod_index;
		
		if (!lod->HasGeometry())
			continue;
		
		ASSERT(lod->m_pNormals && lod->m_pTexCoordsDiffuse);
		
		render::vector<u16> indices;
		init_index_buffer(lod, indices);
		
		lod_info.lods[lod_index].start_index = total_indices.size();
		lod_info.lods[lod_index].num_indices = indices.size();
		
		for (render::vector<u16>::const_iterator it=indices.begin(); it!=indices.end(); ++it)
			total_indices.push_back(*it + u16(total_vertices.size()));
		
        // fill out vertex buffer
		render::vector<frond_vertex> vertices;
		vertices.resize(lod->m_nNumVertices);
		
        frond_vertex* p_vertex = &vertices[0];
        for (s32 vertex_index=0; vertex_index<lod->m_nNumVertices; vertex_index++)
        {
			// position
			vostok::memory::copy(p_vertex->m_afCoord, sizeof(p_vertex->m_afCoord), lod->m_pCoords + vertex_index * 3, sizeof(p_vertex->m_afCoord));
			
			parent.m_bbox.modify(float3(p_vertex->m_afCoord[0], p_vertex->m_afCoord[1], p_vertex->m_afCoord[2]));
			
			// LOD position
			vostok::memory::copy(p_vertex->m_afLodCoord, sizeof(p_vertex->m_afCoord), lod->m_pLodCoords ? lod->m_pLodCoords + vertex_index * 3 : lod->m_pCoords + vertex_index * 3, sizeof(p_vertex->m_afLodCoord));

			// normal
			vostok::memory::copy(p_vertex->m_aucNormal, sizeof(p_vertex->m_afCoord), lod->m_pNormals + vertex_index * 3, sizeof(p_vertex->m_aucNormal));

			// ambient occlusion
			p_vertex->m_ucAmbOcc = lod->m_pAmbientOcclusionValues ? lod->m_pAmbientOcclusionValues[vertex_index] : 255;

			// diffuse texcoords
			p_vertex->m_afDiffuseTexCoords[0] = lod->m_pTexCoordsDiffuse[vertex_index * 2];
			p_vertex->m_afDiffuseTexCoords[1] = lod->m_pTexCoordsDiffuse[vertex_index * 2 + 1];

			// frond ripple / ambient occlusion
			p_vertex->m_afFrondRipple[0] = lod->m_pFrondRipple[vertex_index * 2 + 0];
			p_vertex->m_afFrondRipple[1] = lod->m_pFrondRipple[vertex_index * 2 + 1];

			// tangent
			vostok::memory::copy(p_vertex->m_aucTangent, sizeof(p_vertex->m_afCoord), lod->m_pTangents + vertex_index * 3, sizeof(p_vertex->m_aucTangent));
			p_vertex->m_ucTangentPadding = 0;

			// wind data
			if (lod->m_pWindData)
			{
				p_vertex->m_fWindScalarMag = lod->m_fWindDataMagnitude;
				vostok::memory::copy(p_vertex->m_aucWindData, sizeof(p_vertex->m_afCoord), lod->m_pWindData + vertex_index * 6, sizeof(p_vertex->m_aucWindData));
			}
			else
			{
				p_vertex->m_fWindScalarMag = 0.0f;
				p_vertex->m_aucWindData[0] = p_vertex->m_aucWindData[1] = p_vertex->m_aucWindData[2] = p_vertex->m_aucWindData[3] = 0;
			}
            ++p_vertex;
        }
		
		for (render::vector<frond_vertex>::const_iterator it=vertices.begin(); it!=vertices.end(); ++it)
			total_vertices.push_back(*it);
	}
	
	m_render_geometry.index_count		= total_indices.size();
	m_render_geometry.primitive_count	= m_render_geometry.index_count/3;
	untyped_buffer_ptr ib				= resource_manager::ref().create_buffer( m_render_geometry.index_count*sizeof(u16), 
		&total_indices[0],
		enum_buffer_type_index, 
		false
		);
	
	m_render_geometry.vertex_count		= total_vertices.size();
	bool dynamic						= true;
	u32 stride							= sizeof(frond_vertex);
	untyped_buffer_ptr vb				= resource_manager::ref().create_buffer	(	m_render_geometry.vertex_count * stride, 
		&total_vertices[0],
		enum_buffer_type_vertex, 
		dynamic
		);
	
	m_render_geometry.geom				= resource_manager::ref().create_geometry( &*decl, stride, *vb, *ib);
}

void speedtree_tree_component_frond::init_index_buffer(SpeedTree::SIndexedTriangles const* lod, render::vector<u16>& out_indices)
{
//	const SGeometry* tree_geometry  = m_parent->GetGeometry( );
	
//	st_int32 index_buffer_size = 0;
	/*
	for (s32 mg_index = 0; mg_index < lod->m_nNumMaterialGroups; mg_index++)
	{
		const SDrawCallInfo* info = lod->m_pDrawCallInfo + mg_index;
		index_buffer_size += info->m_nLength;
		
		switch (tree_geometry->m_pMaterials[mg_index].m_eCullType)
		{
		case SpeedTree::CULLTYPE_FRONT:
				m_material_effects.m_cull_mode = D3D_CULL_BACK;
				break;
		case SpeedTree::CULLTYPE_BACK:
				m_material_effects.m_cull_mode = D3D_CULL_FRONT;
				break;
		case SpeedTree::CULLTYPE_NONE:
				m_material_effects.m_cull_mode = D3D_CULL_NONE;
				break;
		}
	}
	*/
	for (s32 mg_index = 0; mg_index < lod->m_nNumMaterialGroups; mg_index++)
	{
		const SDrawCallInfo* info = lod->m_pDrawCallInfo + mg_index;
		
		ASSERT(lod->m_pTriangleIndices16);
		
		for (s32 i=info->m_nOffset; i<info->m_nOffset + info->m_nLength; i++)
			out_indices.push_back(u16(lod->m_pTriangleIndices16[i]));
	}		
}

void speedtree_tree_component_frond::set_material(material_ptr mtl_ptr)
{
// 	material_manager::ref().initialize_material_effects(
// 		m_material_effects, 
// 		mtl_ptr, speedtree_frond_vertex_input_type,
// 		false
// 	);
}

void speedtree_tree_component_frond::set_default_material()
{
//	m_material_effects = material::nomaterial_material(speedtree_frond_vertex_input_type);
}

void speedtree_tree_component_frond::render(lod_entry const* lod, renderer_context* context) 
{
	VOSTOK_UNREFERENCED_PARAMETERS(lod, context);
}

} // namespace render
} // namespace vostok
