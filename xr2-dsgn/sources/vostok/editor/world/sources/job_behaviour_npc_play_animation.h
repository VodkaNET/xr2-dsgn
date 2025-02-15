////////////////////////////////////////////////////////////////////////////
//	Created		: 21.10.2011
//	Author		: Plichko Alexander
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef JOB_BEHAVIOUR_NPC_PLAY_ANIMATION_H_INCLUDED
#define JOB_BEHAVIOUR_NPC_PLAY_ANIMATION_H_INCLUDED
#include "job_behaviour_base.h"

namespace vostok {
namespace editor {

ref class object_job;

public ref class job_behaviour_npc_play_animation : job_behaviour_base {

	typedef vostok::editor::wpf_controls::property_container				wpf_property_container;

public:
	job_behaviour_npc_play_animation( object_job^ parent_job );

	~job_behaviour_npc_play_animation( )
	{
		DELETE( m_animation_behaviour_config );
	}

	virtual void load( configs::lua_config_value const& config ) override;

	virtual void save( configs::lua_config_value& config ) override;

	virtual void get_properties	( wpf_property_container^ to_container )	override;

	virtual System::Collections::Generic::List<System::String^>^ get_available_events_list( ) override; 
	
private:
	void on_select_animation	( wpf_controls::property_editors::property^ , Object^ );
	void on_behaviour_config_loaded( resources::queries_result& data );

public:
	[System::ComponentModel::DisplayNameAttribute("animation")]
	property System::String^		selected_animation;

private:
	System::String^				m_selected_animation_type;
	configs::lua_config_ptr*	m_animation_behaviour_config;

}; // class job_behaviour_light_static

} // namespace editor
} // namespace vostok

#endif // #ifndef JOB_BEHAVIOUR_NPC_PLAY_ANIMATION_H_INCLUDED