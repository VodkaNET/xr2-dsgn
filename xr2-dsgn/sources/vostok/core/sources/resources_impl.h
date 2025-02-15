////////////////////////////////////////////////////////////////////////////
//	Created		: 06.05.2010
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef RESOURCES_IMPL_H_INCLUDED
#define RESOURCES_IMPL_H_INCLUDED

#include "resources_helper.h"

#include <vostok/resources_resource.h>
#include <vostok/resources.h>
#include <vostok/fs/asynchronous_device_interface.h>

namespace vostok {
namespace resources {

void				initialize			(fs_new::asynchronous_device_interface &	hdd,
										 fs_new::asynchronous_device_interface &	dvd,
										 enable_fs_watcher_bool						enable_fs_watcher);

void				mount_mounts_path	(pcstr mounts_path);
bool				is_initialized		();
void				finalize			();

} // namespace vostok
} // namespace resources

#endif // #ifndef RESOURCES_IMPL_H_INCLUDED