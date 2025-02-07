////////////////////////////////////////////////////////////////////////////
//	Created		: 16.02.2011
//	Author		: Sergey Pryshchepa
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////
#ifndef ANIMATIONS_VIEW_SOURCE_H_INCLUDED
#define ANIMATIONS_VIEW_SOURCE_H_INCLUDED

using namespace System;
using namespace System::Windows::Forms;
using vostok::editor::controls::tree_view_source;
using vostok::editor::controls::tree_view;

namespace vostok {
namespace animation_editor {
	ref class animations_node_sorter : public System::Collections::IComparer 
	{
	public:
		virtual int Compare	(Object^ x, Object^ y);
	}; // ref class animations_node_sorter

	ref class animations_view_source : public vostok::editor::controls::tree_view_source
	{
	public:
								animations_view_source	();
		virtual					~animations_view_source	();
		virtual	void			refresh					();
		virtual property		tree_view^		parent
		{
			tree_view^			get						();
			void				set						(tree_view^ value);
		};

	private:
				void	on_fs_iterator_ready			(vostok::vfs::vfs_locked_iterator const & fs_it);
				void	process_fs						(vostok::vfs::vfs_iterator const & it, String^ file_path);

	private:
		tree_view^						m_parent;
	}; // class animations_view_source
}//namespace animation_editor
}//namespace vostok
#endif // #ifndef ANIMATIONS_VIEW_SOURCE_H_INCLUDED