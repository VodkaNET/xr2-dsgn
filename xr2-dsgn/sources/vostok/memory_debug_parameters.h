////////////////////////////////////////////////////////////////////////////
//	Created 	: 25.09.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_DEBUG_PARAMETERS_H_INCLUDED
#define MEMORY_DEBUG_PARAMETERS_H_INCLUDED

#ifdef DEBUG
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION_NO_COMA		pcstr const function, pcstr const file, u32 const line
#	define VOSTOK_CORE_DEBUG_PARAMETERS_UNREFERENCED_GUARD		VOSTOK_UNREFERENCED_PARAMETER(function); \
																VOSTOK_UNREFERENCED_PARAMETER(file); \
																VOSTOK_UNREFERENCED_PARAMETER(line);

#	define VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION				, VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION_NO_COMA
#	define VOSTOK_CORE_DEBUG_PARAMETERS							, function, file, line

#if VOSTOK_PLATFORM_PS3
#	define VOSTOK_CORE_DEBUG_PARAMETERS_TYPEID(T)					, typeid(T).name()
#else 
#	define VOSTOK_CORE_DEBUG_PARAMETERS_TYPEID(T)					, typeid(T).raw_name()
#endif

#	define VOSTOK_CORE_DEBUG_PARAMETERS_DESCRIPTION_DECLARATION	, pcstr const description
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DESCRIPTION				, description
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DESCRIPTION_PARAMETER		description
#else // #ifdef DEBUG
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION_NO_COMA	
#	define VOSTOK_CORE_DEBUG_PARAMETERS_UNREFERENCED_GUARD		
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DECLARATION
#	define VOSTOK_CORE_DEBUG_PARAMETERS
#	define VOSTOK_CORE_DEBUG_PARAMETERS_TYPEID(T)
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DESCRIPTION_DECLARATION
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DESCRIPTION
#	define VOSTOK_CORE_DEBUG_PARAMETERS_DESCRIPTION_PARAMETER		""
#endif // #ifdef DEBUG

#endif // #ifndef MEMORY_DEBUG_PARAMETERS_H_INCLUDED