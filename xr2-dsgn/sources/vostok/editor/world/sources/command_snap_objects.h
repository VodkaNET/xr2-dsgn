////////////////////////////////////////////////////////////////////////////
//	Created		: 02.04.2009
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_SNAP_OBJECTS_H_INCLUDED
#define COMMAND_SNAP_OBJECTS_H_INCLUDED

#include "command_snap_base.h"
#include "project_defines.h"

namespace vostok {
namespace editor {
ref class level_editor;

public ref class command_snap_objects :	public command_snap_base
{
public:
				command_snap_objects	( level_editor^ le );
	virtual		~command_snap_objects	( );


	virtual bool commit					( ) override;
	virtual void rollback				( ) override;
	virtual bool end_preview			( ) override;

private:
	level_editor^			m_level_editor;	
	id_matrices_list		m_id_matrices;
	bool					m_preview_mode;
}; // class command_snap_objects

} // namespace editor
} // namespace vostok

#endif // #ifndef COMMAND_SNAP_OBJECTS_H_INCLUDED