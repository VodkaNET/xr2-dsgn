////////////////////////////////////////////////////////////////////////////
//	Created		: 21.01.2011
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef PCH_H_INCLUDED
#define PCH_H_INCLUDED

#define VOSTOK_LOG_MODULE_INITIATOR	"model_editor"
#include <vostok/editor/base/editor_extensions.h>

#pragma managed( push, off )
#include "model_editor_memory.h"
#pragma managed( pop )

#include <vostok/editor/base/images/images16x16.h>

namespace vostok{
namespace model_editor{

typedef System::Collections::Generic::List<System::String^> string_list;

#include <vostok/editor/base/unmanaged_string.h>
} // namespace model_editor

namespace render {
class world; 
class scene_renderer;
namespace editor{ class renderer; }
namespace debug{ class renderer; }
} // namespace render

namespace collision { 
	struct space_partitioning_tree; 
	class collision_object_geometry;
	class geometry;
	struct primitive;
} // namespace collision

} // namespace vostok

using System::ComponentModel::DisplayNameAttribute;
using System::ComponentModel::DescriptionAttribute;
using System::ComponentModel::CategoryAttribute;
using System::ComponentModel::DefaultValueAttribute;
using System::ComponentModel::ReadOnlyAttribute;
using System::ComponentModel::MergablePropertyAttribute;

#pragma make_public (vostok::memory::doug_lea_allocator_type)
#include <vostok/render/world.h>
#pragma make_public (vostok::render::world)

#endif // #ifndef PCH_H_INCLUDED