////////////////////////////////////////////////////////////////////////////
//	Created		: 23.06.2011
//	Author		: Dmitry Kulikov
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef LISTENER_H_INCLUDED
#define LISTENER_H_INCLUDED

#include <vostok/sound/sound_receiver.h>

namespace vostok {
namespace sound {

class listener : public sound_receiver
{
public:
	virtual command_result_enum		on_sound_event		( sound_producer const& sound_source );	
private:

}; // class listener

} // namespace sound
} // namespace vostok

#endif // #ifndef LISTENER_H_INCLUDED