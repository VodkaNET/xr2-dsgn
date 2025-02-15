﻿////////////////////////////////////////////////////////////////////////////
//	Created		: 26.01.2011
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

using System;

namespace vostok.editor.wpf_controls.color_picker
{
	internal class green_worker: color_part_worker_base
	{
		color_rgb m_rgb_color;

		public override Double color_to_part( color_hsv color )
		{
			m_rgb_color = (color_rgb)color;
			return m_rgb_color.g * 255;
		}
		public override color_hsv part_to_color( Double part )
		{
			m_rgb_color.g = part / 255;
			return (color_hsv)m_rgb_color;
		}
	}
}
