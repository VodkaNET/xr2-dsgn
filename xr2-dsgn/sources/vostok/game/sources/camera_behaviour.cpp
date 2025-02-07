////////////////////////////////////////////////////////////////////////////
//	Created		: 24.05.2011
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "camera_behaviour.h"
#include "object_track.h"
#include "object_scene.h"
#include "game_camera.h"
#include "event_manager.h"
#include "game_world.h"
#include "camera_director.h"

#include <vostok/input/keyboard.h>
#include <vostok/input/gamepad.h>
#include <vostok/input/mouse.h>
#include <vostok/input/world.h>
#include "game.h"

namespace stalker2{

camera_follow_by_track_behaviour::camera_follow_by_track_behaviour( object_scene_job* owner, 
																   configs::binary_config_value const& data, 
																   pcstr name )
:super					( owner, data, name ),
m_track					( NULL ),
m_camera				( NULL ),
m_animation_end_raised	( false )
{
	m_bcyclic			= m_data["cyclic"];
}

void camera_follow_by_track_behaviour::tick( )
{
	R_ASSERT					( m_track );
	float const time			= m_timer.get_elapsed_sec();

	float time_current			= (m_bcyclic) ? fmod(time,m_track_length) : time;
	m_track->evaluate			( time_current, m_camera->inverted_view_matrix( ) );

	if(!m_bcyclic&& time > m_track_length )
	{
		if(!m_animation_end_raised)
		{
			game_event ev("animation_end");
			m_owner->get_event_manager()->emit_event	( ev, m_camera );
			m_animation_end_raised = true;
		}
	}
}

void camera_follow_by_track_behaviour::detach_from_object( object_controlled* o )
{
	R_ASSERT					( m_camera==o );
	super::detach_from_object	( o );
	m_track						= NULL;
	m_camera					= NULL;
}

void camera_follow_by_track_behaviour::attach_to_object( object_controlled* o )
{
	super::attach_to_object		( o );
	m_camera					= static_cast_checked<game_camera*>( o );

	pcstr track_name			= m_data["camera_track"];
	game_object_ptr_ t			= m_owner->get_game_world().get_object_by_name	( track_name );
	R_ASSERT					( t );
	m_track						= static_cast_checked<object_track*>(t.c_ptr());
	R_ASSERT					( m_track );
	m_track_length				= m_track->length();
	m_timer.start				( );
	m_animation_end_raised		= false;
}


camera_free_fly_behaviour::camera_free_fly_behaviour( object_scene_job* owner, 
													 configs::binary_config_value const& data, 
													 pcstr name )
:super				( owner, data, name),
m_start_time_ms		( 0 ),
m_mouse_move		( 0,0,0 )
{
}

camera_free_fly_behaviour::~camera_free_fly_behaviour( )
{
}

bool camera_free_fly_behaviour::on_keyboard_action( vostok::input::world* input_world, 
													vostok::input::enum_keyboard key, 
													vostok::input::enum_keyboard_action action )
{
	VOSTOK_UNREFERENCED_PARAMETERS	( input_world );

	if(action == vostok::input::kb_key_hold)
		m_keyb_events.push_back	( key );
	return false;
}

bool camera_free_fly_behaviour::on_gamepad_action( vostok::input::world* input_world, 
													vostok::input::gamepad_button button, 
													vostok::input::enum_gamepad_action action )
{
	VOSTOK_UNREFERENCED_PARAMETER		(action);

	if ( button == vostok::input::gamepad_x) {
		input_world->get_gamepad()->set_vibration	( input::gamepad_vibrator_left, input_world->get_gamepad()->get_vibration( input::gamepad_vibrator_left ) + 0.01f );
		return					true;
	}

	if ( button == vostok::input::gamepad_b) {
		input_world->get_gamepad()->set_vibration	( input::gamepad_vibrator_right, input_world->get_gamepad()->get_vibration( input::gamepad_vibrator_right ) + 0.01f );
		return					true;
	}
	return	false;
}

bool camera_free_fly_behaviour::on_mouse_key_action(	vostok::input::world* input_world, 
														vostok::input::mouse_button button, 
														vostok::input::enum_mouse_key_action action )
{
	VOSTOK_UNREFERENCED_PARAMETERS	( input_world );

	if(action==vostok::input::ms_key_hold)
		m_mouse_events.push_back	( button );

	return false;
}

bool camera_free_fly_behaviour::on_mouse_move( vostok::input::world* input_world, int x, int y, int z )
{
	VOSTOK_UNREFERENCED_PARAMETERS	( input_world );

	m_mouse_move.x += x;
	m_mouse_move.y += y;
	m_mouse_move.z += z;
	return false;
}

bool camera_free_fly_behaviour::keyb_event_present( int e )
{
	return std::find(m_keyb_events.begin(), m_keyb_events.end(), e) != m_keyb_events.end();
}

bool camera_free_fly_behaviour::mouse_event_present( int e )
{
	return std::find(m_mouse_events.begin(), m_mouse_events.end(), e) != m_mouse_events.end();
}

void camera_free_fly_behaviour::build_view_matrix( vostok::math::float2 const& raw_angles, float const shift_forward, float const shift_right, float const shift_up )
{
	float4x4 const view_inverted	= m_owner->get_game_world().get_camera_director()->get_inverted_view_matrix( );
	float3 const angles_zxy			= view_inverted.get_angles( math::rotation_zxy );

	float3 new_angles_zxy			= float3( raw_angles.x + angles_zxy.x, raw_angles.y+angles_zxy.y, angles_zxy.z );
	new_angles_zxy.x				= math::clamp_r( new_angles_zxy.x, -math::pi_d2, math::pi_d2 );

	float4x4 rotation				= math::create_rotation( new_angles_zxy, math::rotation_zxy );

	float3 const position			=	view_inverted.c.xyz( ) +
										view_inverted.i.xyz( ) * shift_right +
										view_inverted.j.xyz( ) * shift_up +
										view_inverted.k.xyz( ) * shift_forward;

	float4x4 const translation		= math::create_translation( position );

	m_camera->inverted_view_matrix()	= rotation * translation;

	//if(s_type_camera== type_camera_terrain_along_fly)
	//{
	//	if(m_camera->get_game_world().get_collision_tree())
	//	{
	//		collision::ray_objects_type			collision_results( g_allocator );

	//		const float pick_point_height_camera_point = 0.3f;//1000.f;
	//		const float pick_length = 1000.f + pick_point_height_camera_point;
	//		


	//		const float3 pick_point = m_inverted_view_matrix.c.xyz() + float3( 0, pick_point_height_camera_point, 0 );
	//		
	//		const float3 dir( 0, -1, 0 );

	//		bool ray_query_result = m_camera->get_game_world().get_collision_tree()->ray_query(
	//									collision_object_type_terrain,
	//									pick_point,
	//									dir,
	//									pick_length,  
	//									collision_results, 
	//									collision::objects_predicate_type( )
	//								);

	//		if(ray_query_result)
	//			m_inverted_view_matrix.c.xyz().y = ( pick_point.y - collision_results[0].distance + s_terrain_fly_height );
	//	}	
	//}
}

void camera_free_fly_behaviour::attach_to_object( object_controlled* o )
{
	super::attach_to_object( o );
	m_camera = static_cast_checked<game_camera*>( o );
	m_owner->get_game_world().get_game().input_world().add_handler(*this);
	m_start_time_ms			= m_owner->get_game_world().get_game().time_ms();
}

void camera_free_fly_behaviour::detach_from_object( object_controlled* o )
{
	super::detach_from_object( o );
	m_owner->get_game_world().get_game().input_world().remove_handler(*this);
}

void camera_free_fly_behaviour::tick( )
{
	super::tick				( );


#if VOSTOK_PLATFORM_WINDOWS
	u32 const game_time_ms		= m_owner->get_game_world().get_game().time_ms( );

	ASSERT						( game_time_ms >= m_start_time_ms );
	float const time_delta		= float( game_time_ms - m_start_time_ms );

	float factor				= 60.f * 0.001f * time_delta;
	float angle_factor			= 0.5f;

	m_start_time_ms				= game_time_ms;

	if( m_keyb_events.empty() && 
		m_mouse_events.empty() && 
		math::is_zero(m_mouse_move.x) && math::is_zero(m_mouse_move.y) && math::is_zero(m_mouse_move.z) )
		return;

	if ( keyb_event_present(input::key_lcontrol) || keyb_event_present(input::key_rcontrol) )
		factor					*= 20.f;

	if ( keyb_event_present( input::key_lshift ) || keyb_event_present( input::key_rshift ) )
		factor					*= .1f;

	if ( keyb_event_present( input::key_lalt ) || keyb_event_present( input::key_ralt ) ) 
		angle_factor			*= .1f;

	float						forward = 0.f;
	float						right	= 0.f;
	float						up		= 0.f;

	if ( mouse_event_present(input::mouse_button_left) )
		forward					+= factor*.1f;
	
	if ( mouse_event_present(input::mouse_button_right) )
		forward					-= factor*.1f;

	if ( keyb_event_present(input::key_d) )
		right				+= factor*.1f;
	
	if ( keyb_event_present(input::key_a) )
		right				-= factor*.1f;
	
	if ( keyb_event_present(input::key_w) )
		up					+= factor*.1f;
	
	if ( keyb_event_present(input::key_s) )
		up					-= factor*.1f;

	float const	angle_x			= angle_factor * math::deg2rad( m_mouse_move.y );
	float const	angle_y			= angle_factor * math::deg2rad( m_mouse_move.x ) * 0.75f;
	build_view_matrix			( float2( angle_x, angle_y ), forward, right, up );

	m_keyb_events.clear();
	m_mouse_events.clear();
	m_mouse_move.x = 0.0f;
	m_mouse_move.y = 0.0f;
	m_mouse_move.z = 0.0f;
#else
	//raw<gamepad>::ptr const gamepad	= m_game_world.get_game().input_world().get_gamepad();
	//if ( !( gamepad->get_state().buttons & input::gamepad_x ) )
	//	gamepad->set_vibration	( input::gamepad_vibrator_left, gamepad->get_vibration( input::gamepad_vibrator_left ) - .01f );

	//if ( !( gamepad->get_state().buttons & input::gamepad_b ) )
	//	gamepad->set_vibration	( input::gamepad_vibrator_right, gamepad->get_vibration( input::gamepad_vibrator_right ) - .01f );

	//ASSERT						( gamepad );
	//gamepad::state const& state	= gamepad->get_state ( );
	//u32 const game_time_ms		= m_game_world.get_game().time_ms( );
	//float const time_delta		= float( game_time_ms - m_start_time_ms );
	//m_start_time_ms				= game_time_ms;
	//float						factor = 10.f*.001f*time_delta;
	//build_view_matrix			(
	//	float2(
	//		state.left_thumb_stick.y*.001f,
	//		state.left_thumb_stick.x*.001f*.75f
	//	),
	//	( state.left_trigger - state.right_trigger ) * factor,
	//	state.right_thumb_stick.x,
	//	state.right_thumb_stick.y
	//);
#endif
}


camera_director_behaviour::camera_director_behaviour( object_scene_job* owner, 
													 configs::binary_config_value const& data, 
													 pcstr name )
:super( owner, data, name)
{}

void camera_director_behaviour::attach_to_object( object_controlled* o )
{
	super::attach_to_object( o );
	pcstr camera_name			= m_data["active_camera"];
	game_object_ptr_ t			= m_owner->get_game_world().get_object_by_name	( camera_name );
	R_ASSERT					( t );
	game_camera* c				= static_cast_checked<game_camera*>(t.c_ptr());

	m_owner->get_game_world().get_camera_director()->switch_to_camera( c, camera_name );
}

void camera_director_behaviour::detach_from_object( object_controlled* o )
{
	super::detach_from_object( o );
}

}