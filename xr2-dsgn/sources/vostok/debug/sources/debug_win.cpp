////////////////////////////////////////////////////////////////////////////
//	Created 	: 06.10.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vostok/debug/extensions.h>
#include <vostok/debug/call_stack.h>
#include "platform.h"
#include "utils.h"
#include "call_stack.h"

#include <dxerr.h>
#pragma comment( lib, "dxerr.lib" )

static pcstr s_full_call_stack_line_format	= "%-60s(%-3d) : %-70s : %-36s : 0x%08x";
static pcstr s_call_stack_line_format		= "%-60s       : %-70s : 0x%08x";

#ifdef DEBUG
#	define USE_OWN_ERROR_MESSAGE_WINDOW	1
#else // #ifdef DEBUG
#	define USE_OWN_ERROR_MESSAGE_WINDOW	0
#endif // #ifdef DEBUG

static bool s_error_after_dialog	= false;

struct helper {
	string512				m_initiator;
	bool					m_use_error_verbosity;


	u32						m_num_first_to_ignore;
	u32						m_num_last_to_ignore;

	helper		(	pcstr const						initiator, 
					bool const						use_error_verbosity, 
					u32								num_first_to_ignore,
					u32								num_last_to_ignore) :
		m_use_error_verbosity	( use_error_verbosity ),
		m_num_first_to_ignore	( num_first_to_ignore ),
		m_num_last_to_ignore	( num_last_to_ignore )
	{
		strcpy_s						( m_initiator, initiator );
		strcat_s						( m_initiator, ":");
	}

	bool	predicate	(
			u32 	call_stack_id,
			u32 	num_call_stack_lines,
			pcstr 	module_name,
			pcstr 	file_name,
			int		line_number,
			pcstr	function,
			size_t	address
		)
	{
		if ( call_stack_id < m_num_first_to_ignore )
			return					( true );

		if ( call_stack_id >= num_call_stack_lines - m_num_last_to_ignore )
			return					( true );

		string4096	string;
		if ( line_number > 0 )
			sprintf_s				( string, s_full_call_stack_line_format, file_name, line_number, function, module_name, address );
		else
			sprintf_s				( string, s_call_stack_line_format, module_name, function, address);

		vostok::debug::log_callback const log_callback	=	vostok::debug::get_log_callback();
		if ( log_callback )		
			log_callback			( m_initiator, m_use_error_verbosity, true, string );
				
		return						( true );
	}
}; // struct helper

bool vostok::debug::platform::error_after_dialog	( )
{
	return							( s_error_after_dialog );
}

void vostok::debug::dump_call_stack				( pcstr						initiator,
												  bool						use_error_verbosity, 
												  u32						num_first_to_ignore, 
												  u32						num_last_to_ignore,
												  _EXCEPTION_POINTERS*		pointers,
												  void*						call_stack[])
{
	helper							temp( initiator, use_error_verbosity, num_first_to_ignore, num_last_to_ignore );
	debug::call_stack::iterate( pointers, call_stack, boost::bind( &helper::predicate, &temp, _1, _2, _3, _4, _5, _6, _7 ), true );
}

struct error_helper {
	u32		m_ignore_level_count;
	pstr	m_start_buffer;
	pstr	m_buffer;
	u32		m_buffer_size;

							error_helper	(
			u32 const ignore_level_count,
			pstr const buffer,
			u32 const buffer_size
		) :
		m_ignore_level_count	( ignore_level_count ),
		m_start_buffer			( buffer ),
		m_buffer				( buffer ),
		m_buffer_size			( buffer_size )
	{
	}

					bool	predicate	(
			u32		call_stack_id,
			u32		num_call_stack_lines,
			pcstr	module_name,
			pcstr	file_name,
			int		line_number,
			pcstr	function,
			size_t	address
		)
	{
		VOSTOK_UNREFERENCED_PARAMETER	( num_call_stack_lines );
		
		static pcstr s_full_call_stack_line_format_local	= "%s(%d) : %s : %s : 0x%08x";
		static pcstr s_call_stack_line_format_local			= "%s       : %s : 0x%08x";

		if ( call_stack_id < m_ignore_level_count)
			return					( true );

		if ( line_number > 0 )
			m_buffer				+= sprintf_s(
				m_buffer,
				m_buffer_size - ( m_buffer - m_start_buffer ),
				s_full_call_stack_line_format_local,
				file_name,
				line_number,
				function,
				module_name,
				address
			);
		else
			m_buffer				+= sprintf_s(
				m_buffer,
				m_buffer_size - ( m_buffer - m_start_buffer ),
				s_call_stack_line_format_local,
				module_name,
				function,
				address
			);

		m_buffer					+= sprintf_s( m_buffer, m_buffer_size - ( m_buffer - m_start_buffer ), "\r\n" );
		return						( m_buffer_size - ( m_buffer - m_start_buffer ) >= 384 );
	}
}; // struct helper

void vostok::debug::platform::on_error	( bool* do_debug_break, char* const message, u32 const message_size, bool* ignore_always, _EXCEPTION_POINTERS* const exception_information, error_type_enum error_type )
{
	VOSTOK_UNREFERENCED_PARAMETERS	( exception_information, ignore_always, message_size );

	if ( do_debug_break )
		* do_debug_break			= false;

	if ( vostok::debug::is_debugger_present() ) {
		vostok::debug::on_error ( message );
		return;
	}

#if USE_OWN_ERROR_MESSAGE_WINDOW
	call_stack_size_calculator		calculator;
	vostok::debug::call_stack::iterate( NULL, NULL, boost::bind( & call_stack_size_calculator::predicate, &calculator, _1, _2, _3, _4, _5, _6, _7), false );
	u32 const message_length		= strlen( message );
	u32 const buffer_size			= calculator.needed_size() + message_length + 4096;
	pstr buffer						= static_cast<pstr>( ALLOCA( buffer_size ) );
	memcpy							( buffer, message, message_length );
	buffer							+= message_length;
	
	error_helper					helper (error_type == error_type_assert ? 3 : 0, buffer, u32 ( message_size - ( buffer - message ) ) );
	vostok::debug::call_stack::iterate( exception_information, NULL, boost::bind( &error_helper::predicate, &helper, _1, _2, _3, _4, _5, _6, _7), false );

	buffer							= message + strlen( message );

	pcstr const	endline				= "\r\n";

	if ( error_type == error_type_assert )
	{
		buffer						+= sprintf_s( buffer, message_size - ( buffer - message ), "%s%sPress CANCEL to abort execution%s", endline, endline, endline );
		buffer						+= sprintf_s( buffer, message_size - ( buffer - message ), "Press TRY AGAIN to continue execution%s", endline );
		buffer						+= sprintf_s( buffer, message_size - ( buffer - message ), "Press CONTINUE to continue execution and ignore all the errors of this type%s%s", endline, endline );
	}
	else
	{
		buffer						+= sprintf_s( buffer, message_size - ( buffer - message ), "%s%sPress OK to abort execution%s", endline, endline, endline );
	}

	int	const result				= 
		MessageBox	(
			GetTopWindow( 0 ),
			message,
			"Fatal Error",
			( error_type == error_type_assert ? MB_CANCELTRYCONTINUE : MB_OK ) | MB_ICONERROR | MB_SYSTEMMODAL
		);

	if ( error_type == error_type_unhandled_exception )
		return;

	s_error_after_dialog			= true;

	switch (result) {
		case IDCANCEL : {
			if ( do_debug_break )
				* do_debug_break	= true;
			vostok::debug::on_error ( message );
			break;
		}
		case IDTRYAGAIN : {
			s_error_after_dialog	= false;
			break;
		}
		case IDCONTINUE : {
			s_error_after_dialog	= false;
			if ( ignore_always )
				*ignore_always		= true;
			break;
		}
		default : {
			if ( do_debug_break )
				* do_debug_break	= true;
			vostok::debug::on_error ( message );
			break;
		}
	}
#else // #if USE_OWN_ERROR_MESSAGE_WINDOW
	if ( error_type == error_type_unhandled_exception )
		return;

	if ( do_debug_break )
		* do_debug_break			= true;

	vostok::debug::on_error		( message );
#endif // #if USE_OWN_ERROR_MESSAGE_WINDOW
}

void vostok::debug::platform::on_error_message_box	( bool* do_debug_break, char* const message, u32 const message_size, bool* ignore_always, _EXCEPTION_POINTERS* const exception_information, error_type_enum error_type )
{
	VOSTOK_UNREFERENCED_PARAMETERS	( exception_information, ignore_always, error_type );

	if ( do_debug_break )
		* do_debug_break			= false;

	pstr buffer						= message + strlen( message );
	pcstr const	endline				= "\r\n";

	buffer							+= sprintf_s( buffer, message_size - (buffer - message), "%s%sPress OK to abort execution%s", endline, endline, endline );
	MessageBox	(
			GetTopWindow(0),
			message,
			"Fatal Error",
			MB_OK | MB_ICONERROR | MB_SYSTEMMODAL
		);

	vostok::debug::on_error		( message );
}

void vostok::debug::debug_message_box (pcstr message)
{
	MessageBox						( 0, message, "Debug Break", MB_OK );
}

void vostok::debug::platform::terminate				( pcstr message, int const error_code  )
{
	if ( *message )
		MessageBox					( 0, message, "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL );

	TerminateProcess				( GetCurrentProcess(), error_code );
	::exit							( error_code );	// to suppress warnings
}

pstr vostok::debug::platform::fill_format_message	( int const error_code )
{
	pstr							result;
	FormatMessage					( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 0, error_code, 0, (LPSTR)&result, 0, 0 );
	return							( result );
}

void vostok::debug::platform::free_format_message	( pstr const buffer )
{
	LocalFree						( buffer );
}

pcstr vostok::debug::platform::get_graphics_api_error_description	( int const error_code )
{
	return							DXGetErrorDescription( error_code );
}

bool vostok::debug::is_debugger_present( )
{
	return							IsDebuggerPresent() == TRUE;
}

void vostok::debug::notify_xbox_debugger ( pcstr message )
{
	VOSTOK_UNREFERENCED_PARAMETER		( message );
}
