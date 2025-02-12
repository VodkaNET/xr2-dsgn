////////////////////////////////////////////////////////////////////////////
//	Created		: 11.03.2010
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_TERRAIN_EXCHANGE_TEXTURE_H_INCLUDED
#define COMMAND_TERRAIN_EXCHANGE_TEXTURE_H_INCLUDED

#include <vostok/render/facade/base_command.h>
#include <vostok/render/facade/common_types.h>
#include <vostok/render/engine/base_classes.h>

namespace vostok {
namespace render {

class world;

class terrain_exchange_texture_command :
	public base_command,
	private boost::noncopyable
{
public:
					terrain_exchange_texture_command	(
						vostok::render::engine::world& world,
						scene_ptr const& in_scene,
						fs_new::virtual_path_string const& old_texture,
						fs_new::virtual_path_string const& new_texture
					);
	virtual	void	execute								( );

private:
	engine::world&	m_render_engine_world;
	scene_ptr		m_scene_ptr;
	fs_new::virtual_path_string	m_old;
	fs_new::virtual_path_string	m_new;
}; // class terrain_exchange_texture_command

} // namespace render
} // namespace vostok

#endif // #ifndef COMMAND_TERRAIN_EXCHANGE_TEXTURE_H_INCLUDED