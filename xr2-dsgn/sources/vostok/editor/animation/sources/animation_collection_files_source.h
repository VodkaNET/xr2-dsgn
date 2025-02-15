////////////////////////////////////////////////////////////////////////////
//	Created		: 06.10.2011
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef ANIMATION_COLLECTION_FILES_SOURCE_H_INCLUDED
#define ANIMATION_COLLECTION_FILES_SOURCE_H_INCLUDED

using namespace System;
using vostok::editor::controls::tree_view_source;
using vostok::editor::controls::tree_view;

namespace vostok
{
	namespace animation_editor
	{
		ref class animation_collection_files_source: public vostok::editor::controls::tree_view_source
		{
		public:
									animation_collection_files_source	( );
			virtual					~animation_collection_files_source	( );
			virtual	void			refresh					( );
			virtual property		tree_view^		parent
			{
				tree_view^			get						( );
				void				set						( tree_view^ value );
			};
			
					void			fs_callback				( vostok::vfs::vfs_notification const & info );

		private:
					void	on_fs_iterator_ready			( vostok::vfs::vfs_locked_iterator const & fs_it );
					void	process_fs						( vostok::vfs::vfs_iterator const & it,  String^ file_path );

		private:
			tree_view^						m_parent;
			file_watcher_delegate*			m_callback;
			u32								m_subscribe_id;

		}; // class animation_collection_files_source
	} // namespace animation_editor
} // namespace vostok

#endif // #ifndef ANIMATION_COLLECTION_FILES_SOURCE_H_INCLUDED