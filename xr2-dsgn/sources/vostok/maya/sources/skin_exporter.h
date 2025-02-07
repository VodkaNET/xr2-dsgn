////////////////////////////////////////////////////////////////////////////
//	Created		: 08.07.2010
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef SKIN_EXPORTER_H_INCLUDED
#define SKIN_EXPORTER_H_INCLUDED

namespace vostok{
namespace maya{

class skinned_visual_exporter : public MPxCommand
{
public:
	static const MString			Name;

public:
	virtual MStatus			doIt		( const MArgList& );
	virtual bool			isUndoable	( ) const		{ return false; } 

	static void*			creator		( );
	static MSyntax			newSyntax	( );

private:
	MStatus				check_args			( MArgDatabase& arg_data );
	MString				m_folder_name;
}; // class skinned_visual_exporter

} //namespace maya
} //namespace vostok

#endif // #ifndef SKIN_EXPORTER_H_INCLUDED