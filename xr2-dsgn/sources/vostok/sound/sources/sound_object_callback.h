////////////////////////////////////////////////////////////////////////////
//	Created		: 16.04.2010
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef SOUND_OBJECT_CALLBACK_H_INCLUDED
#define SOUND_OBJECT_CALLBACK_H_INCLUDED

#include <vostok/intrusive_spsc_queue.h>

namespace vostok {
namespace sound {

class sound_world;
class sound_object_impl;

struct callback_command
{
	enum cb_event{ev_unknown, ev_stream_end, ev_buffer_end, ev_buffer_error};

				callback_command		( cb_event const& ev, sound_object_impl* owner, void* context):m_event_type(ev),m_owner(owner),m_context(context){ };
				~callback_command		( )		{};
		void	execute					( );

	callback_command*		m_next;
	cb_event				m_event_type;
	sound_object_impl*		m_owner;
	void*					m_context;
}; // struct callback_command

typedef intrusive_spsc_queue<callback_command, callback_command, &callback_command::m_next>	callback_commands_queue_type;

} // namespace sound
} // namespace vostok

#endif // #ifndef SOUND_OBJECT_CALLBACK_H_INCLUDED