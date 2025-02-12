////////////////////////////////////////////////////////////////////////////
//	Created		: 25.03.2009
//	Author		: Mykhailo Parfeniuk
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef FVF_H_INCLUDED
#define FVF_H_INCLUDED

namespace vostok {
namespace render {

#pragma pack(push,4)

namespace vertex_formats
{
	struct L 
	{
		float3		p;
		u32			color;
		void		set(const L& src) {*this = src;};
		void		set(float x, float y, float z, u32 C) { p.set(x,y,z); color=C; }
		void		set(const float3& _p, u32 C) { p = _p; color=C; }
	};

	//const u32 F_L		= D3DFVF_XYZ | D3DFVF_DIFFUSE;
	const D3D_INPUT_ELEMENT_DESC F_L[] = 
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM,	0, 12, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};


	struct V 
	{
		float3		p;
		float2		t;
		void		set(const V& src) {*this = src;};
		void		set(float x, float y, float z, float u, float v)	{ p.set(x,y,z); t.set(u,v);}
		void		set(const float3& _p,float u, float v)				{ p=(_p);	t.set(u,v);}
	};
	//const u32 F_V		= D3DFVF_XYZ | D3DFVF_TEX1;
	const D3D_INPUT_ELEMENT_DESC F_V[] = 
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 12, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};

	struct Tuv 
	{
		float4		p;
		float2		t;
		void		set(const Tuv& src) {*this = src;};
		void		set(float x, float y, float z, float w, float u, float v)	{ p.set(x,y,z,w); t.set(u,v);}
		void		set(const float4& _p,float u, float v)				{ p=(_p);	t.set(u,v);}
	};
	//const u32 F_V		= D3DFVF_XYZ | D3DFVF_TEX1;
	const D3D_INPUT_ELEMENT_DESC F_Tuv [] = 
	{
		{"POSITIONT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};

	struct LIT {
		float3		p;
		u32			color;
		float2		t;
		void		set(const LIT& src) {*this = src;};
		void		set(float x, float y, float z, u32 C, float u, float v) { p.set(x,y,z); color=C; t.set(u,v);}
		void		set(const float3& _p, u32 C, float u, float v) { p=(_p); color=C; t.set(u,v);}
	};

	//const u32 F_LIT	= D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	const D3D_INPUT_ELEMENT_DESC F_LIT[] = 
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM,	0, 12, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};

	struct TL0uv {
		float4	p;
		u32			color;
		void	set	(const TL0uv& src)
		{	*this = src; };
		void	set	(float x, float y, u32 c)
		{	set	(x,y,.0001f,.9999f,c); };
		void	set	(int x, int y, u32 c)
		{	set	(float(x),float(y),.0001f,.9999f,c); };
		void	set	(float x, float y, float z, float w, u32 c)
		{	p.set	(x,y,z,w); color = c; };
		void transform(const float3 &v,const float4x4 &matSet)
		{
			// Transform it through the matrix set. Takes in mean projection.
			// Finally, scale the vertices to screen coords.
			// Note 1: device coords range from -1 to +1 in the viewport.
			// Note 2: the p.z-coordinate will be used in the z-buffer.
			p.w =   matSet.e03*v.x + matSet.e13*v.y + matSet.e23*v.z + matSet.e33;
			float div_p_w = 1.f/p.w;
			p.x	=  (matSet.e00*v.x + matSet.e10*v.y + matSet.e20*v.z + matSet.e30)*div_p_w;
			p.y	= -(matSet.e01*v.x + matSet.e11*v.y + matSet.e21*v.z + matSet.e31)*div_p_w;
			p.z	=  (matSet.e02*v.x + matSet.e12*v.y + matSet.e22*v.z + matSet.e32)*div_p_w;
		};
	};
	//const u32 F_TL0uv	= D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	const D3D_INPUT_ELEMENT_DESC F_TL0uv[] = 
	{
		{"POSITIONT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0},
	};


	struct TL {
		float4	p;
		u32		color;
		float2	uv;
		void	set	(const TL& src)
		{	*this = src; };
		void	set	(float x, float y, u32 c, float2& t)
		{	set	(x,y,.0001f,.9999f,c,t.x,t.y); };
		void	set	(float x, float y, u32 c, float u, float v)
		{	set	(x,y,.0001f,.9999f,c,u,v); };
		void	set	(int x, int y, u32 c, float u, float v)
		{	set	(float(x),float(y),.0001f,.9999f,c,u,v); };
		void	set	(float x, float y, float z, float w, u32 c, float u, float v)
		{	p.set	(x,y,z,w); color = c;	uv.x=u; uv.y=v;	};
		void transform(const float3 &v,const float4x4 &matSet)
		{
			// Transform it through the matrix set. Takes in mean projection.
			// Finally, scale the vertices to screen coords.
			// Note 1: device coords range from -1 to +1 in the viewport.
			// Note 2: the p.z-coordinate will be used in the z-buffer.
			p.w =   matSet.e03*v.x + matSet.e13*v.y + matSet.e23*v.z + matSet.e33;
			float div_p_w = 1.f/p.w;
			p.x	=  (matSet.e00*v.x + matSet.e10*v.y + matSet.e20*v.z + matSet.e30)*div_p_w;
			p.y	= -(matSet.e01*v.x + matSet.e11*v.y + matSet.e21*v.z + matSet.e31)*div_p_w;
			p.z	=  (matSet.e02*v.x + matSet.e12*v.y + matSet.e22*v.z + matSet.e32)*div_p_w;
		};
	};
	//const u32 F_TL	= D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	const D3D_INPUT_ELEMENT_DESC F_TL[] = 
	{
		{"POSITIONT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 20, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};

	struct TL2uv 
	{
		float4	p;
		u32		color;
		float2	uv[2];

		void	set	(const TL2uv& src)
		{	*this = src; };
		void	set	(float x, float y, u32 c, float2& t0, float2& t1)
		{	set	(x,y,.0001f,.9999f,c,t0.x,t0.y,t1.x,t1.y);	};
		void	set	(float x, float y, float z, float w, u32 c, float2& t0, float2& t1)
		{	set	(x,y,z,w,c,t0.x,t0.y,t1.x,t1.y);			};
		void	set	(float x, float y, u32 c, float u, float v, float u2, float v2)
		{	set	(x,y,.0001f,.9999f,c,u,v,u2,v2); };
		void	set	(int x, int y, u32 c, float u, float v, float u2, float v2)
		{	set	(float(x),float(y),.0001f,.9999f,c,u,v,u2,v2); };
		void	set	(float x, float y, float z, float w, u32 c, float u, float v, float u2, float v2)
		{	p.set	(x,y,z,w); color = c; uv[0].x=u; uv[0].y=v;	uv[1].x=u2; uv[1].y=v2;	};
		void transform(const float3 &v,const float4x4 &matSet)
		{
			// Transform it through the matrix set. Takes in mean projection.
			// Finally, scale the vertices to screen coords.
			// Note 1: device coords range from -1 to +1 in the viewport.
			// Note 2: the p.z-coordinate will be used in the z-buffer.
			p.w =   matSet.e03*v.x + matSet.e13*v.y + matSet.e23*v.z + matSet.e33;
			float div_p_w = 1.f/p.w;
			p.x	=  (matSet.e00*v.x + matSet.e10*v.y + matSet.e20*v.z + matSet.e30)*div_p_w;
			p.y	= -(matSet.e01*v.x + matSet.e11*v.y + matSet.e21*v.z + matSet.e31)*div_p_w;
			p.z	=  (matSet.e02*v.x + matSet.e12*v.y + matSet.e22*v.z + matSet.e32)*div_p_w;
		};
	};
	//const u32 F_TL2uv	= D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2;
	const D3D_INPUT_ELEMENT_DESC F_TL2uv[] = 
	{
		{"POSITIONT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 20, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	1, DXGI_FORMAT_R32G32_FLOAT,		0, 28, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};


	struct TL4uv {
		float4	p;
		u32			color;
		float2	uv[4];
		void	set	(const TL4uv& src)
		{	*this = src; };
		void	set	(float x, float y, u32 c, float2& t0, float2& t1)
		{	set	(x,y,.0001f,.9999f,c,t0.x,t0.y,t1.x,t1.y);	};
		void	set	(float x, float y, float z, float w, u32 c, float2& t0, float2& t1)
		{	set	(x,y,z,w,c,t0.x,t0.y,t1.x,t1.y);			};
		void	set	(float x, float y, u32 c, float u, float v, float u2, float v2)
		{	set	(x,y,.0001f,.9999f,c,u,v,u2,v2); };
		void	set	(int x, int y, u32 c, float u, float v, float u2, float v2)
		{	set	(float(x),float(y),.0001f,.9999f,c,u,v,u2,v2); };
		void	set	(float x, float y, float z, float w, u32 c, float u, float v, float u2, float v2)
		{	p.set	(x,y,z,w); color = c; uv[0].x=u; uv[0].y=v;	uv[1].x=u2; uv[1].y=v2;	};
	};
	//const u32 F_TL4uv	= D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX4;
	const D3D_INPUT_ELEMENT_DESC F_TL4uv[] = 
	{
		{"POSITIONT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM,		0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 20, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	1, DXGI_FORMAT_R32G32_FLOAT,		0, 28, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	2, DXGI_FORMAT_R32G32_FLOAT,		0, 36, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	3, DXGI_FORMAT_R32G32_FLOAT,		0, 44, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};


	struct Tquad
	{
		float4	p;
		float3	eye_ray;
		float2	uv;

		void	set	(const Tquad& src)
		{	*this = src; };
		void	set	(float x, float y, float eye_x, float eye_y, float eye_z, float u, float v)
		{	set	(x,y,.0001f,.9999f, eye_x, eye_y, eye_z, u, v); };
		void	set	(int x, int y, float eye_x, float eye_y, float eye_z, float u, float v)
		{	set	(float(x),float(y),.0001f,.9999f, eye_x, eye_y, eye_z, u, v); };
		void	set	(float x, float y, float z, float w, float eye_x, float eye_y, float eye_z, float u, float v)
		{	p.set	(x,y,z,w); eye_ray.set(eye_x, eye_y, eye_z); uv.x=u; uv.y=v; };
		void transform(const float3 &v,const float4x4 &matSet)
		{
			// Transform it through the matrix set. Takes in mean projection.
			// Finally, scale the vertices to screen coords.
			// Note 1: device coords range from -1 to +1 in the viewport.
			// Note 2: the p.z-coordinate will be used in the z-buffer.
			p.w =   matSet.e03*v.x + matSet.e13*v.y + matSet.e23*v.z + matSet.e33;
			float div_p_w = 1.f/p.w;
			p.x	=  (matSet.e00*v.x + matSet.e10*v.y + matSet.e20*v.z + matSet.e30)*div_p_w;
			p.y	= -(matSet.e01*v.x + matSet.e11*v.y + matSet.e21*v.z + matSet.e31)*div_p_w;
			p.z	=  (matSet.e02*v.x + matSet.e12*v.y + matSet.e22*v.z + matSet.e32)*div_p_w;
		};
	};

	//const u32 F_TL2uv	= D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2;
	const D3D_INPUT_ELEMENT_DESC F_Tquad[] = 
	{
		{"POSITIONT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 16, 	D3D_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 28, 	D3D_INPUT_PER_VERTEX_DATA, 0}
	};


} // namespace vertex_formats
#pragma pack(pop)

} // namespace render
} // namespace vostok

#endif // #ifndef FVF_H_INCLUDED