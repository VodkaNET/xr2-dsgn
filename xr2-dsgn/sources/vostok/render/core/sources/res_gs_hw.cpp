////////////////////////////////////////////////////////////////////////////
//	Created		: 06.04.2010
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <vostok/render/core/res_gs_hw.h>
#include <vostok/render/core/res_xs_hw.h>
#include <vostok/render/core/device.h>
#include <vostok/render/core/res_xs_hw_impl.h>

namespace vostok {
namespace render {

template<>
HRESULT res_xs_hw<gs_data>::create_hw_shader( ID3DBlob* shader_code, ID3DGeometryShader **hardware_shader)
{
	void const* bytecode_buffer	= shader_code->GetBufferPointer();
	u32 bytecode_buffer_size	= (u32)shader_code->GetBufferSize();

#if USE_DX10
	return device::ref().d3d_device()->CreateGeometryShader ( bytecode_buffer, bytecode_buffer_size, hardware_shader);
#else
	return device::ref().d3d_device()->CreateGeometryShader ( bytecode_buffer, bytecode_buffer_size, NULL, hardware_shader);
#endif
}

template class res_xs_hw<gs_data>;

} // namespace render
} // namespace vostok
