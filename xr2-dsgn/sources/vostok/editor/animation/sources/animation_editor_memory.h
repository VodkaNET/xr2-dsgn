////////////////////////////////////////////////////////////////////////////
//        Created                : 18.08.2010
//        Author                : Sergey Pryshchepa
//        Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef ANIMATION_EDITOR_MEMORY_H_INCLUDED
#define ANIMATION_EDITOR_MEMORY_H_INCLUDED

#include <vostok/editor/animation/api.h>

namespace vostok {
namespace animation_editor {

extern allocator_type*						g_allocator;

#define USER_ALLOCATOR						*::vostok::animation_editor::g_allocator
#include <vostok/std_containers.h>
#include <vostok/unique_ptr.h>
#undef USER_ALLOCATOR

} // namespace animation_editor
} // namespace vostok

#define NEW( type )								VOSTOK_NEW_IMPL(*::vostok::animation_editor::g_allocator, type )
#define DELETE( pointer )                       VOSTOK_DELETE_IMPL(*::vostok::animation_editor::g_allocator, pointer )
#define MALLOC( size, description )             VOSTOK_MALLOC_IMPL(*::vostok::animation_editor::g_allocator, size, description )
#define REALLOC( pointer, size, description )   VOSTOK_REALLOC_IMPL(*::vostok::animation_editor::g_allocator, pointer, size, description )
#define FREE( pointer )                         VOSTOK_FREE_IMPL(*::vostok::animation_editor::g_allocator, pointer )
#define ALLOC( type, count )                    VOSTOK_ALLOC_IMPL(*::vostok::animation_editor::g_allocator, type, count )

#endif // #ifndef ANIMATION_EDITOR_MEMORY_H_INCLUDED
