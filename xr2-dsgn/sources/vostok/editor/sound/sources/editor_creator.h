////////////////////////////////////////////////////////////////////////////
//	Created		: 10.06.2010
//	Author		: Sergey Pryshchepa
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////
#ifndef EDITOR_CREATOR_H_INCLUDED
#define EDITOR_CREATOR_H_INCLUDED

namespace vostok {
namespace sound_editor {
	public ref class editor_creator
	{
	public:
		static vostok::editor_base::tool_window^	create_editor		( System::String^ resources_path, 
																		sound::world& sound_world, 
																		render::world& render_world, 
																		vostok::editor_base::tool_window_holder^ h );

		static void								set_memory_allocator( allocator_type* allocator );
	}; // ref class editor_creator
} // namespace sound_editor
} // namespace vostok
#endif // #ifndef VOSTOK_DIALOG_EDITOR_API_H_INCLUDED