////////////////////////////////////////////////////////////////////////////
//	Created 	: 29.08.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_LOGGING_EXTENSIONS_H_INCLUDED
#define VOSTOK_LOGGING_EXTENSIONS_H_INCLUDED

#if VOSTOK_CORE_BUILDING
#	define VOSTOK_LOG_MODULE_INITIATOR			"core"
#endif // #if VOSTOK_CORE_BUILDING

#ifndef VOSTOK_LOG_MODULE_INITIATOR
#	error you should define VOSTOK_LOG_MODULE_INITIATOR macro before including this header
#endif // #ifndef VOSTOK_LOG_MODULE_INITIATOR

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vostok/logging/helper.h>
#include <vostok/logging/format_specifier.h>

namespace vostok {
namespace logging {

enum log_flags_enum {
	log_to_console		=	1 << 0,
	log_to_stderr		=	1 << 1,
};

extern format_specifier		format_thread_id;
extern format_specifier		format_initiator;
extern format_specifier		format_time;
extern format_specifier		format_verbosity;
extern format_specifier		format_message;

enum callback_flag {
	first	= 1 << 0,
	last	= 1 << 1,
}; // enum callback_flag

typedef	boost::function<
	void (
		pcstr,					// file
		pcstr,					// function signature
		int	 ,					// line
		int	 ,					// verbosity
		pcstr,					// log string
		callback_flag   		// first/last string
	)
>				log_callback;

VOSTOK_LOGGING_API	void			flush_log_file		( pcstr file_name = 0 );

VOSTOK_LOGGING_API	void			set_log_callback	( log_callback callback );
VOSTOK_LOGGING_API	log_callback	get_log_callback	( );

VOSTOK_LOGGING_API	void			push_filter			( pcstr							initiator, 
														  int							verbosity, 
														  memory::base_allocator *		allocator,
														  u32 const						thread_id = u32(-1));

VOSTOK_LOGGING_API	void			pop_filter			( );

VOSTOK_LOGGING_API	void			set_format			( format_specifier const & format_expression );

} // namespace logging
} // namespace vostok

#include <vostok/logging/macros.h>

#endif // #ifndef VOSTOK_LOGGING_EXTENSIONS_H_INCLUDED