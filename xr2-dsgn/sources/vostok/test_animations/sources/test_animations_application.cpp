////////////////////////////////////////////////////////////////////////////
//	Created		: 07.12.2009
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "test_animations_application.h"

pcstr test_animations::application::get_resources_path		( ) const
{
	UNREACHABLE_CODE(return 0);
}

#if 0
#	include "skeleton.h"
#	include "../../animation/sources/animation_data.h"
#	include <vostok/resources_queries_result.h>
#	include <vostok/configs_lua_config.h>
#	include <vostok/resources_fs.h>
#	include <vostok/os_include.h>
#	include "maya_animation_data.h"
#	define DELETE( pointer )						VOSTOK_DELETE_IMPL(	::vostok::animation::g_allocator, pointer )

using test_animations::application;
using vostok::float4x4;
using vostok::animation::animation_data;
using vostok::animation::animation_data_discret;
using vostok::animation::test_skeleton;
using vostok::animation::animation_data_hermite;

#ifdef	DEBUG
using vostok::static_cast_checked;
#endif

vostok::memory::doug_lea_allocator_type	vostok::animation::g_allocator;

namespace vostok {
namespace animation {

struct test_skeleton
{
	vostok::animation::vector<float4x4>	m_bones;
};

} // namespace animation
} // namespace vostok

void application::initialize	( )
{

	m_exit_code					= 0;

	vostok::core::preinitialize					( this, vostok::core::no_log, GetCommandLine( ), vostok::command_line::contains_application_true, "test_animations" );

	vostok::animation::g_allocator.do_register	( 500*1024*1024, "test animation allocator" );
	vostok::memory::allocate_region				( );

	vostok::core::initialize						( "main", vostok::core::perform_debug_initialization );

	for( u32 i= 0; i< num_data ; ++i )
	{
		m_data[i]			= NEW (animation_data) ();
		m_data_discret[i]	= NEW(animation_data_discret)();
		m_data_hermite[i]	= NEW(animation_data_hermite)();
	}
	m_skel					= NEW (test_skeleton) ();
}

void application::finalize		( )
{
	for( u32 i= 0; i< num_data ; ++i )
		DELETE( m_data[i] );

	for( u32 i= 0; i< num_data ; ++i )
		DELETE( m_data_discret[i] );

	DELETE						( m_skel );

	vostok::core::finalize		( );
}

static void on_skeleton_loaded	( vostok::resources::queries_result& data )
{
	R_ASSERT									( !data.is_failed() );

	vostok::configs::binary_config_ptr config_ptr	= static_cast_checked<vostok::configs::binary_config*>(data[0].get_unmanaged_resource().get());
	vostok::animation::skeleton skeleton			= vostok::animation::skeleton( config_ptr->get_root() );
}

static void on_mounted_disk		( bool const result )
{
	VOSTOK_UNREFERENCED_PARAMETER	( result );
	R_ASSERT					( result );
}

template<class data_type>
 void application::test_anim(data_type* data[num_data], pcstr name  )
 {
	u32 bone_cnt = data[0]->anim_bone_count();
	m_skel->m_bones.resize( bone_cnt , float4x4().identity() );
	
	const float min_time =  m_data[0]->min_time();
	const float max_time =  m_data[0]->max_time();
	
	const float interval		= max_time - min_time;
	const u32	frame_count		= 2000;
	const u32	path_count		= num_data;
	const float dt				= interval/frame_count;
	
	vostok::timing::timer t;
	t.start						( );
	for(u32 k =0; k < path_count; ++k )
	{
		for(u32 i =0; i < frame_count; ++i )
		{
			float time = min_time + i * dt;
			for( u32 j=0; j < bone_cnt; ++j )
				data[k]->bone_pose( m_skel->m_bones[j], j, time );
		}
	}
	float time = t.get_elapsed_sec();

	float per_frame = time/frame_count/path_count;
	float ms_per_frame  = per_frame * 1000;
	
	const u32 bones_per_obj = 100;
	const u32 num_objects = 100;
	const u32 num_frames = 33;

	float empiric_cost = ms_per_frame * bones_per_obj * num_objects / bone_cnt * num_frames; 

	LOG_INFO("empiric_cost %s %f", name,  empiric_cost );
	LOG_INFO("ms_per_frame %s %f", name, ms_per_frame );
}

//template < typename T, int capacity >
//class spsc_queue {
//public:
//	inline bool empty				( ) const
//	{
//		return						!m_buffer[m_consumer_index];
//	}
//
//	inline bool push_back			( T const value )
//	{
//		if ( m_buffer[m_producer_index] )
//			wait_while_full			( );
//
//		m_producer_event.set		(false);
//		m_buffer[m_producer_index]	= value;
//		bool result					= m_producer_index == m_consumer_index;
//		m_producer_index			= (m_producer_index + 1) % capacity;
//		return						result;
//	}
//
//	inline T pop_front				( )
//	{
//		R_ASSERT					( !empty() );
//		if ( !m_buffer[m_producer_index] ) {
//		}
//		else {
//			m_producer_event.set	(true);
//		}
//
//		int value					= m_buffer[m_consumer_index];
//		m_buffer[m_consumer_index]	= 0;
//		m_consumer_index			= (m_consumer_index + 1) % capacity;
//		return						value;
//	}
//
//private:
//	void __declspec(noinline) wait_while_full	( )
//	{
//		for ( u32 i=0; i < 1000; ++i ) {
//			if ( !m_buffer[m_producer_index] )
//				break;
//		}
//
//		m_producer_event.wait		( 0 );
//	}
//
//private:
//	VOSTOK_MAX_CACHE_LINE_PAD;
//	vostok::threading::event	m_producer_event;
//	int						m_producer_index; 
//	VOSTOK_MAX_CACHE_LINE_PAD;
//	int						m_consumer_index; 
//	VOSTOK_MAX_CACHE_LINE_PAD;
//	int						m_buffer[capacity];
//};

struct base {
	base* mega_next;
}; // struct base

#include <vostok/intrusive_spsc_queue.h>

void application::execute		( )
{
	
	vostok::resources::start_mount_transaction	( );
 	vostok::resources::query_mount_disk	(
		"resources", 
 		"../../resources", 
		true,
 		on_mounted_disk, 
		&vostok::animation::g_allocator
	);
 	vostok::resources::end_mount_transaction	( );

	{
		vostok::intrusive_spsc_queue<base,base,&base::mega_next>	queue;
		queue.set_push_thread_id( );
		queue.set_pop_thread_id	( );
		queue.push_null_node	( NEW(base) );

		queue.push_back			( NEW(base) );
		queue.push_back			( NEW(base) );
		queue.push_back			( NEW(base) );
		queue.push_back			( NEW(base) );

		base* value, *to_delete	= 0;
		value					= queue.pop_front( to_delete );
		DELETE					( to_delete );
		value					= queue.pop_front( to_delete );
		DELETE					( to_delete );
		value					= queue.pop_front( to_delete );
		DELETE					( to_delete );
		value					= queue.pop_front( to_delete );
		DELETE					( to_delete );

		value					= queue.pop_null_node();
		DELETE					( value );
	}

	for ( u32 i=0; i < num_data; ++i )
	for( u32 i=0; i < num_data; ++i )
	{
		ASSERT						(m_data[i]);

		if ( m_data[i]->load( "supper_test.track") )
		//if ( m_data[i]->load( "walk_tect_2000_01.track") )
		//if ( m_data[i]->load( "walk_tect_joint_animation_2000_01.track") )
		//if ( m_data[i]->load( "stancia_2_05_07_per.track") )
		{
			m_data_discret[i]->build( *m_data[i] );
			m_data_hermite[i]->build( *m_data[i] );
		}
	}
	m_data_discret_channels.load( "1.dschtrack.track" );

	for( u32 i = 0; i < 100 ; ++i)
	{
		test_anim( m_data, "polinomial" );
		test_anim( m_data_discret, "linear" );

		test_anim( m_data_hermite, "hermite" );
	}
	vostok::resources::query_resource(
		"resources/animation/skeletons/human.lua",
		vostok::resources::binary_config_class,
		&on_skeleton_loaded,
		&vostok::animation::g_allocator
	);

	//for ( ;; ) {
	//	vostok::resources::dispatch_callbacks	( );
	//	vostok::threading::yield	( 10 );
	//}
	
}

void application::exit			( int exit_code )
{
	
	std::exit					( exit_code );
}

void application::set_exit_code	( int exit_code )
{
	m_exit_code					= exit_code;
}

int application::get_exit_code	( ) const
{
	return						m_exit_code;
}

#endif