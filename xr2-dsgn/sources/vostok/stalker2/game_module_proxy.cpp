////////////////////////////////////////////////////////////////////////////
//	Created		: 23.03.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <vostok/stalker2/game_module_proxy.h>
#include <vostok/game/api.h>

using stalker2::game_module_proxy;
using vostok::engine_user::world;

world* game_module_proxy::create_world						(
		vostok::engine_user::engine& engine, 
		vostok::render::world& render_world, 
		vostok::sound::world& sound,
		vostok::network::world& network
	)
{
	return
		stalker2::game_module::create_world(
			engine, 
			render_world,
			sound,
			network
		);
}

void game_module_proxy::destroy_world						( vostok::engine_user::world*& world )
{
	stalker2::game_module::destroy_world				( world );
}

void game_module_proxy::register_memory_allocators			( )
{
	stalker2::game_module::register_memory_allocators	( );
}

vostok::memory::doug_lea_allocator_type& game_module_proxy::allocator	( )
{
	return	stalker2::game_module::allocator( );
}