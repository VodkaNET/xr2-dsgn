////////////////////////////////////////////////////////////////////////////
//	Created		: 22.04.2010
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef SOUND_STREAM_COOK_H_INCLUDED
#define SOUND_STREAM_COOK_H_INCLUDED

#include <vostok/resources_cook_classes.h>

namespace vostok {
namespace sound {

class sound_world;

class sound_stream_cook :	public resources::translate_query_cook,
							public boost::noncopyable
{
	typedef resources::translate_query_cook	super;
public:
							sound_stream_cook		( );
	virtual					~sound_stream_cook	( );

	virtual void			delete_resource			( resources::resource_base* res);
	virtual void			translate_query			( resources::query_result_for_cook& parent );

private:
			void			on_sub_resources_loaded	( resources::queries_result& data ); // raw ogg file loaded
			void			on_raw_properties_loaded( resources::queries_result& result );
}; // class sound_stream_cook


} // namespace sound
} // namespace vostok

#endif // #ifndef SOUND_STREAM_COOK_H_INCLUDED