////////////////////////////////////////////////////////////////////////////
//	Created		: 21.04.2009
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_PASTE_OBJECTS_H_INCLUDED
#define COMMAND_PASTE_OBJECTS_H_INCLUDED

#include "project_defines.h"
#include <vostok/configs_lua_config.h>

namespace vostok {
namespace editor {

ref class level_editor;

public ref class command_paste_objects :	public vostok::editor_base::command
{
public:

							command_paste_objects	( level_editor^ le, vostok::configs::lua_config_value const& cfg );
	virtual					~command_paste_objects	();

	virtual bool			commit		() override;
	virtual void			rollback	() override;

private:
	level_editor^					m_level_editor;
	configs::lua_config_value*		m_cfg;
	string_list						m_loaded_names;
}; // class command_paste_objects

}// namespace editor
}// namespace vostok

#endif // #ifndef COMMAND_PASTE_OBJECTS_H_INCLUDED