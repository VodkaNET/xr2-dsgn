////////////////////////////////////////////////////////////////////////////
//	Created 	: 26.08.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "stalker2_ps3_application.h"
#include <vostok/engine/api.h>

using stalker2::application;

void application::initialize( pcstr const command_line )
{
	m_exit_code					= 0;
	vostok::engine::preinitialize	( m_game_proxy, command_line, "stalker2", __DATE__ );
	vostok::engine::initialize	( );
}

void application::finalize	( )
{
	vostok::engine::finalize		( );
}

void application::execute	( )
{
	vostok::engine::execute		( );
}