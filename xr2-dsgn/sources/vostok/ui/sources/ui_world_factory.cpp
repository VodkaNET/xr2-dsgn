////////////////////////////////////////////////////////////////////////////
//	Created		: 03.02.2009
//	Author		: Andrew Kolomiets
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////
#include "pch.h"

#include "ui_world.h"
#include "ui_dialog.h"
#include "ui_image.h"
#include "ui_text_edit.h"
#include "ui_scroll_view.h"
#include "ui_progress_bar.h"

namespace vostok {
namespace ui {

window* ui_world::create_window( )
{
	return VOSTOK_NEW_IMPL( allocator(), ui_window )(allocator());
}

dialog* ui_world::create_dialog( )
{
	return VOSTOK_NEW_IMPL( allocator(), ui_dialog )(allocator());
}

text* ui_world::create_text( )
{
	return VOSTOK_NEW_IMPL( allocator(), ui_text<static_text> )(*this);
}

text_edit* ui_world::create_text_edit( )
{
	return VOSTOK_NEW_IMPL( allocator(), ui_text_edit )(*this, te_standart, allocator());
}

image* ui_world::create_image( )
{
	return VOSTOK_NEW_IMPL( allocator(), ui_image )(allocator());
}

scroll_view* ui_world::create_scroll_view( )
{
	return VOSTOK_NEW_IMPL( allocator(), ui_scroll_view )(allocator());
}

void ui_world::destroy_window(window* w)
{
	VOSTOK_DELETE_IMPL( allocator(), w );
}

vostok::ui::font const* ui_world::default_font()
{
	return get_font_manager().get_font();
}

progress_bar* ui_world::create_progress_bar( )
{
	return VOSTOK_NEW_IMPL		( allocator( ), ui_progress_bar )( *this );
}

} // namespace vostok
} // namespace ui
