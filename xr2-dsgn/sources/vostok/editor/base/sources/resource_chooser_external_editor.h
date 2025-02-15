////////////////////////////////////////////////////////////////////////////
//	Created		: 02.12.2011
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef RESOURCE_CHOOSER_EXTERNAL_EDITOR_H_INCLUDED
#define RESOURCE_CHOOSER_EXTERNAL_EDITOR_H_INCLUDED

using namespace System;

using vostok::editor::wpf_controls::property_editors::i_external_property_editor;
using vostok::editor::wpf_controls::property_editors::i_additional_data;
using vostok::editor::wpf_controls::property_editors::property;

namespace vostok
{
	namespace editor_base
	{

		public ref class resource_chooser_external_editor: i_external_property_editor, i_additional_data
		{
		public:
			virtual property		String^				additional_data;
			virtual		void		run_editor			( property^ prop );
		}; // class resource_chooser_external_editor

	} // namespace editor_base
} // namespace vostok

#endif // #ifndef RESOURCE_CHOOSER_EXTERNAL_EDITOR_H_INCLUDED