////////////////////////////////////////////////////////////////////////////
//	Created 	: 29.08.2008
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "path_parts.h"
#include <vostok/logging/api.h>
#include <vostok/logging/helper.h>
#include <vostok/logging/extensions.h>
#include <vostok/logging/log_file.h>
#include <vostok/buffer_string.h>
#include <stdarg.h>						// for va_list
#include <vostok/fs/native_path_string.h>
#include <vostok/fs/device_utils.h>
#include <vostok/debug/log_callback.h>

#include "logging.h"
#include "globals.h"

using vostok::logging::helper;
using vostok::logging::helper_data;
using vostok::logging::path_parts;
using vostok::logging::log_callback;
using vostok::logging::log_file;

static log_callback				s_log_callback	= 0;

vostok::logging::log_file_usage	 get_log_file_usage ();

namespace vostok {
namespace logging {

void fill_local_time( vostok::buffer_string& dest );

void set_log_callback			(log_callback callback)
{
	ASSERT						(callback);
	s_log_callback				= callback;
}

log_callback get_log_callback	()
{
	return						( s_log_callback );
}

int get_tree_verbosity			( path_parts* const path );
void log_thread_unsafe			( logging::log_flags_enum const log_flags, pcstr string, u32 string_length, logging::verbosity verbosity );

} // namespace logging
} // namespace vostok

helper_data::helper_data		(
		pcstr const file,
		pcstr const function_signature,
		int const line,
		pcstr const initiator,
		vostok::logging::verbosity const verbosity
	) :
	m_file					( file ),
	m_function_signature	( function_signature ),
	m_line					( line ),
	m_verbosity				( verbosity ),
	m_initiator				( initiator )
{
}

helper::helper					(
		pcstr const file,
		pcstr const function_signature,
		int const line,
		pcstr const initiator,
		vostok::logging::verbosity const verbosity
	) :
	helper_data				(
		file,
		function_signature,
		line,
		initiator,
		verbosity
	)
{
}

static void fill_log_string				( vostok::buffer_string &					dest,
										  pcstr const							message_start, 
										  pcstr const							message_end, 
										  vostok::logging::path_parts &			path, 
										  int const								verbosity,
										  vostok::logging::log_format const &		format )
{
	using namespace vostok;
	using namespace vostok::logging;

	format_string_type	strings_storage		[format_specifier_count];
	buffer_string *		strings				[format_specifier_count];
	for ( int i=0; i<format_specifier_count; ++i )
		strings[i]						=	& strings_storage[i];

	u32 const message_length			=	message_end - message_start;
	buffer_string	message_string			((pstr)message_start, message_length + 1, message_length);
	char const saved_end_char			=	* message_end;
	* (pstr)message_end					=	NULL;

	strings[format_specifier_message]	=	& message_string;
	
	if ( format.enabled[format_specifier_initiator] )
	{
		path.concat2buffer					(* strings[format_specifier_initiator]);

		for ( pstr	i	=	(* strings[format_specifier_initiator]).begin(),
					end	=	(* strings[format_specifier_initiator]).end();
					i != end; ++i )
		{
			if ( *i == '/' )	
				*i						=	':';
		}
	}
	if ( format.enabled[format_specifier_thread_id] )
	{
		(* strings[format_specifier_thread_id]).assignf	("%-8s", vostok::threading::current_thread_logging_name());
	}
	if ( format.enabled[format_specifier_time] )
	{
		fill_local_time						(* strings[format_specifier_time]);
	}
	if ( format.enabled[format_specifier_verbosity] )
	{
		* strings[format_specifier_verbosity]	=	verbosity_to_string(verbosity);
	}

	COMPILE_ASSERT							(format_specifier_count == 7, OMG_FIX_BELOW_THEN);
	dest.assignf							(format.string.c_str(),
 												(* strings[format.indexes[0]]).c_str(), 
												(* strings[format.indexes[1]]).c_str(),
 												(* strings[format.indexes[2]]).c_str(), 
												(* strings[format.indexes[3]]).c_str(),
 												(* strings[format.indexes[4]]).c_str(), 
												(* strings[format.indexes[5]]).c_str());

	* (pstr)message_end					=	saved_end_char;
}

struct predicate : private vostok::logging::noncopyable
{
	pcstr											m_file;
	pcstr											m_function_signature;
	int												m_line;
	vostok::logging::verbosity						m_verbosity;
	vostok::logging::log_flags_enum const				m_log_flags;
	vostok::logging::log_format const &				m_format;
	vostok::logging::path_parts &						m_path;

	inline		predicate		(
			pcstr const 									file,
			pcstr const 									function_signature,
			int const										line,
			vostok::logging::verbosity const					verbosity,
			vostok::logging::log_flags_enum const				log_flags,
			vostok::logging::path_parts &						path,
			vostok::logging::log_format const &				format
		) :
		m_file					( file ),
		m_function_signature	( function_signature ),
		m_line					( line ),
		m_verbosity				( verbosity ),
		m_log_flags				( log_flags ),
		m_path					( path ),
		m_format				( format )
	{
	}

	inline bool	operator ( )	( u32 const index, pcstr string, u32 const length, bool const is_last ) const
	{
		char const	end_line[]			=	"\r\n";
		u32 const	end_line_length		=	vostok::array_size(end_line) - 1; // counts trailing zero, so need to -1
		u32 const	final_length		=	128 + length + end_line_length + 1;

		vostok::buffer_string	final_string	((pstr)ALLOCA(final_length*sizeof(char)), final_length);

		fill_log_string						(final_string, string, string+length, 
											 m_path, m_verbosity, m_format);

		vostok::threading::mutex_raii	raii	(vostok::logging::globals->log_mutex);

		final_string.append					( "\n" );
		vostok::debug::output					( final_string.c_str() );
		vostok::buffer_string::iterator const end	= final_string.begin() + final_string.length();
		final_string.erase					( end - 1, end );
		final_string.append					(end_line, end_line+end_line_length);
		vostok::logging::log_thread_unsafe	(m_log_flags, final_string.c_str(), final_string.length(), m_verbosity);

		if ( s_log_callback ) {
			s_log_callback		(
				m_file,
				m_function_signature,
				m_line,
				m_verbosity, 
				string,
				!index ? vostok::logging::first : ( is_last ? vostok::logging::last : vostok::logging::callback_flag( 0 ) )
			);
		}

		return								( true );
	}
}; // struct predicate

void	vostok::logging::log_format::set	(vostok::logging::format_specifier const & format_expression)
{
	format_specifier_list					specifiers;
	format_expression.fill_specifier_list	(specifiers, & string);
	for ( u32 i=0; i<format_specifier_count; ++i )
	{
		indexes[ i ]					=	0;
		enabled[ i ]					=	false;
	}

	for ( u32 i=0; i<specifiers.size(); ++i )
	{
		indexes[ i ]					=	(int)specifiers[i];
		enabled[ specifiers[i] ]		=	true;
	}
}

static void process				(
		helper_data &									helper,
		vostok::logging::format_specifier const *			log_format_specifier, 
		vostok::logging::log_format const *				log_format, 
		vostok::logging::log_flags_enum const				log_flags,
		pcstr const										format, 
		va_list const									args
	)
{
	using namespace vostok::logging;

	debug_log_disable_raii					debug_log_disable;

	path_parts								path(helper.m_initiator);
	
	vostok::logging::log_format				local_format;
	if ( log_format_specifier )
		local_format.set					(* log_format_specifier);

	vostok::logging::log_format const * format_to_use	=	log_format_specifier ? & local_format : & globals->format;
	if ( log_format )
		format_to_use					=	log_format;

	string4096								message_buffer;
	vostok::vsnprintf							( message_buffer, sizeof( message_buffer ) - 1, format, args );

	vostok::strings::iterate_items	(
		message_buffer,
		predicate (
			helper.m_file,
			helper.m_function_signature,
			helper.m_line,
			helper.m_verbosity,
			log_flags,
			path,
			* format_to_use
		),
		'\n'
	);
}

void helper::operator ( )	( pcstr const format, ... )
{
	va_list	 				mark;
	va_start 				( mark, format );
	process	 				( *this, NULL, NULL, (log_flags_enum)0, format, mark );
	va_end	 				( mark );
}

void helper::operator ( )	( vostok::logging::log_flags_enum const log_flags, pcstr const format, ... )
{
	va_list	 				mark;
	va_start 				( mark, format );
	process	 				( *this, NULL, NULL, log_flags, format, mark );
	va_end	 				( mark );
}

void helper::operator ( )	( vostok::logging::format_specifier const & log_format, pcstr format, ... )
{
	va_list	 				mark;
	va_start 				( mark, format );
	process	 				( *this, & log_format, NULL, (vostok::logging::log_flags_enum)0, format, mark );
	va_end	 				( mark );
}

void helper::operator ( )	( vostok::logging::format_specifier const &	log_format, 
							  int const	log_flags, 
							  pcstr format, 
							  ... )
{
	va_list	 				mark;
	va_start 				( mark, format );
	process	 				( *this, & log_format, NULL, (vostok::logging::log_flags_enum)log_flags, format, mark );
	va_end	 				( mark );
}

void helper::operator( )	( vostok::logging::log_format * const format_struct, int const log_flags, pcstr format, ... )
{
	va_list	 				mark;
	va_start 				( mark, format );
	process	 				( *this, NULL, format_struct, (vostok::logging::log_flags_enum)log_flags, format, mark );
	va_end	 				( mark );
}

bool vostok::logging::check_verbosity (pcstr initiator, verbosity verbosity)
{
	debug_log_disable_raii					debug_log_disable;

	path_parts								path(initiator);
	
	int const allowed_verbosity			=	get_tree_verbosity( &path );
	if ( verbosity > allowed_verbosity )
		return								false;

	return									true;
}