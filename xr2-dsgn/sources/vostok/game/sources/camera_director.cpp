////////////////////////////////////////////////////////////////////////////
//	Created		: 04.05.2011
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "camera_director.h"
#include "game_world.h"
#include "game.h"
#include "game_camera.h"
#include <vostok/console_command.h>

namespace stalker2{

camera_director::camera_director( game_world& w )
:game_object_		( w ),
m_active_camera		( NULL )
{
	static vostok::console_commands::cc_float3 cc_cam_pos	("camera_pos", m_inverted_view.c.xyz(), float3(-1000,-1000,-1000), float3(1000,1000,1000), false, vostok::console_commands::command_type_user_specific);

	set_position_direction	( float3( 16.f, 10.f, 0.f ), float3( -1.f,  -1.f, 0.f ).normalize() );

	float aspect( 4.f/3.f );
	float fov( 57.5f*math::pi/180.0f );

	m_projection		= math::create_perspective_projection( fov/aspect, aspect, 0.2f, 5000.0f );
}

void camera_director::set_position_direction( math::float3 const& p, math::float3 const& d )
{
	m_inverted_view				=  math::invert4x3(math::create_camera_direction( p, d, float3(0.f, 1.f, 0.f ) ) );
}

void camera_director::tick( )
{
	if(m_active_camera)
	{
		m_active_camera->tick	( );
		m_inverted_view			= m_active_camera->get_inverted_view_matrix();
		m_projection			= m_active_camera->get_projection_matrix();
	}

	m_game_world.get_game().apply_camera(this);
}

void camera_director::switch_to_camera( game_camera* c, pcstr camera_name )
{
	LOG_ERROR("switching to camera %s", camera_name );

	bool bfocused = m_game_world.is_active();

	if(m_active_camera)
	{
		if(m_active_camera==c)
			return;

		if(bfocused)
			m_active_camera->on_focus	( false );

		m_active_camera->on_deactivate	( );
	}

	m_active_camera = c;

	if(m_active_camera)
	{
		m_active_camera->on_activate( this );

		if(bfocused)
			m_active_camera->on_focus	( true );
	}
}

void camera_director::on_focus( bool b_focus_enter )
{
	if(m_active_camera)
		m_active_camera->on_focus( b_focus_enter );
}

} //namespace stalker2
