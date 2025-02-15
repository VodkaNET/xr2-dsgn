////////////////////////////////////////////////////////////////////////////
//	Created 	: 13.10.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef BUILD_EXTENSIONS_H_INCLUDED
#define BUILD_EXTENSIONS_H_INCLUDED

namespace vostok {
namespace build {
					void	preinitialize				( pcstr const build_date );
					void	initialize					( core::engine * );
	VOSTOK_CORE_API	u32		calculate_build_id			( pcstr current_date );
					bool	print_build_id_command_line ( );
	VOSTOK_CORE_API	pcstr	build_date					( );
	VOSTOK_CORE_API	u32		build_station_build_id		( );
} // namespace build
} // namespace vostok

#endif // #ifndef BUILD_EXTENSIONS_H_INCLUDED