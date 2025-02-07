#include "pch.h"
#include "scalable_scroll_bar.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Reflection;

typedef	Drawing::Point Point;

namespace vostok
{
	namespace editor
	{
		namespace controls
		{
			void		scalable_scroll_bar::in_constructor					()
			{
				m_direction				= Direction::Horizontal;

				m_scroller_pen			= gcnew Pen(Color::Black);
				m_scroller_brush		= gcnew SolidBrush(SystemColors::Control);
				m_scroller_brush_active	= gcnew SolidBrush(SystemColors::ControlDark);
				m_alpha_scroller_pen	= gcnew Pen(Drawing::Color::DarkCyan);
				m_alpha_scroller_brush	= gcnew SolidBrush(Color::FromArgb(60, Color::LightBlue));

				m_scroller_panel->GetType()->
					GetProperty("ResizeRedraw", BindingFlags::NonPublic|BindingFlags::Instance|BindingFlags::Public)->
					SetValue(m_scroller_panel, true, nullptr);
				m_scroller_panel->GetType()->
					GetProperty("DoubleBuffered", BindingFlags::NonPublic|BindingFlags::Instance|BindingFlags::Public)->
					SetValue(m_scroller_panel, true, nullptr);
			}

			//Properties
			void		scalable_scroll_bar::direction::set(Direction value)
			{
				if(value == Direction::Horizontal)
				{
					m_move_left_button->Dock			= DockStyle::Left;
					m_move_right_button->Dock			= DockStyle::Right;
					m_left_button_slot_panel->Dock		= DockStyle::Left;
					m_right_button_slot_panel->Dock		= DockStyle::Right;
					m_left_button_slot_panel->Width		= 0;
					m_right_button_slot_panel->Width	= 0;
				}
				else
				{
// 					m_move_left_button->Text			= "▲";
// 					m_move_right_button->Text			= "▼";
					m_move_left_button->Dock			= DockStyle::Top;
					m_move_right_button->Dock			= DockStyle::Bottom;
					m_left_button_slot_panel->Dock		= DockStyle::Top;
					m_right_button_slot_panel->Dock		= DockStyle::Bottom;
					m_left_button_slot_panel->Height	= 0;
					m_right_button_slot_panel->Height	= 0;
				}
				m_direction = value;
				set_scroller(m_scroller_position, m_scroller_width);
			}
			
			void		scalable_scroll_bar::scroller_position::set(Single value)
			{
				set_scroller(value, m_scroller_width);
			}

			//Functions
			void		scalable_scroll_bar::compute_values_on_scale					()
			{
				m_scale_factor				= (
					(direction == Direction::Horizontal)?m_scroller_panel->ClientSize.Width:m_scroller_panel->ClientSize.Height)
					/(m_scroll_max-m_scroll_min);
				m_scroller_rect_tr			= (direction == Direction::Horizontal)?
					Drawing::Rectangle((int)Math::Floor((m_scroller_position-m_scroll_min)*m_scale_factor), 1, (int)Math::Floor(m_scroller_width*m_scale_factor), m_scroller_panel->ClientSize.Height-3):
					Drawing::Rectangle((int)Math::Floor((m_scroller_position-m_scroll_min)*m_scale_factor), 1, (int)Math::Floor(m_scroller_width*m_scale_factor), m_scroller_panel->ClientSize.Width-3);
			}

			void		scalable_scroll_bar::set_scroller					(Single set_position, Single set_width)
			{
				set_scroller	(set_position, set_width, true);
			}

			void		scalable_scroll_bar::set_scroller					(Single set_position, Single set_width, Boolean need_send_message)
			{
				Single last_position	= m_scroller_position;
				Single last_width		= m_scroller_width;

				m_scroller_position		= set_position;
				m_scroller_width		= set_width;

				if(m_scroller_width > m_scroll_max - m_scroll_min)		m_scroller_width		= m_scroll_max - m_scroll_min;
				if(m_scroller_position<m_scroll_min)					m_scroller_position		= m_scroll_min;
				if(m_scroller_position+m_scroller_width>m_scroll_max)	m_scroller_position		= m_scroll_max-m_scroller_width;

				compute_values_on_scale	();
				m_scroller_panel->Invalidate();

				if(need_send_message)
					scroller_moved(this, gcnew scroller_event_args(last_position, m_scroller_position, last_width, m_scroller_width));
			}

			void		scalable_scroll_bar::set_scrollbar					(Single scroll_min, Single scroll_max, Single set_position, Single set_width)
			{
				set_scrollbar	(scroll_min, scroll_max, set_position, set_width, true);
			}

			void		scalable_scroll_bar::set_scrollbar					(Single scroll_min, Single scroll_max, Single set_position, Single set_width, Boolean need_send_message)
			{
				m_scroll_min	= scroll_min;
				m_scroll_max	= scroll_max;
				
				set_scroller	(set_position, set_width, need_send_message);
			}

			Int32		scalable_scroll_bar::transform_mouse(DPoint mouse_pos)
			{
				return (direction == Direction::Horizontal)?mouse_pos.X:mouse_pos.Y;
			}

			void		scalable_scroll_bar::scalable_scroll_bar_VisibleChanged	(System::Object^  sender, System::EventArgs^  e)
			{
				if(this->Visible == false)
					m_is_scroller_cached = false;
			}

			//Events
			void		scalable_scroll_bar::m_scroller_panel_Resize		(System::Object^ , System::EventArgs^ )
			{
				compute_values_on_scale();
			}

			void		scalable_scroll_bar::m_move_left_button_Click		(System::Object^ , System::EventArgs^ )
			{
				scroller_position -= (m_scroll_max-m_scroll_min)/50;
			}

			void		scalable_scroll_bar::m_move_right_button_Click		(System::Object^ , System::EventArgs^ )
			{
				scroller_position += (m_scroll_max-m_scroll_min)/50;
			}

			void		scalable_scroll_bar::m_scroller_panel_MouseLeave	(System::Object^ , System::EventArgs^ )
			{
				m_is_over_scrollbar			= false;
				m_is_over_scroller			= false;
				m_is_over_l_scale			= false;
				m_is_over_r_scale			= false;
				m_scroller_panel->Cursor	=  Windows::Forms::Cursors::Default;

				m_scroller_panel->Invalidate();
			}

			void		scalable_scroll_bar::m_scroller_panel_MouseEnter	(System::Object^ , System::EventArgs^ )
			{
				m_is_over_scrollbar			= true;
			}

			void		scalable_scroll_bar::m_scroller_panel_MouseMove		(System::Object^ , System::Windows::Forms::MouseEventArgs^  e)
			{	
				Int32	mouse_location = transform_mouse(e->Location);

				if		(m_is_scroller_cached)
				{
					scroller_position			= (mouse_location-m_delta_mouse_to_scroller_pos)/m_scale_factor+m_scroll_min;
				}
				else if	(m_is_l_scale_cached)
				{
					Single new_pos		= (mouse_location-m_delta_mouse_to_scroller_pos)/m_scale_factor+m_scroll_min;
					if(m_scroller_position + m_scroller_width - new_pos < c_min_scroller_width/m_scale_factor)
						new_pos = m_scroller_position + m_scroller_width - c_min_scroller_width/m_scale_factor;
					if(new_pos < m_scroll_min){new_pos = m_scroll_min;}
					Single new_width	= m_scroller_width + scroller_position - new_pos;
					set_scroller(new_pos, new_width);
				}
				else if	(m_is_r_scale_cached)
				{
					Single new_r_pos	= (mouse_location+m_delta_mouse_to_scroller_r_pos)/m_scale_factor+m_scroll_min;
					Single new_width		= new_r_pos-m_scroller_position;
					if(new_width < c_min_scroller_width/m_scale_factor) new_width = c_min_scroller_width/m_scale_factor;
					if(m_scroller_position + new_width > m_scroll_max) new_width = m_scroll_max - m_scroller_position;
					set_scroller(m_scroller_position, new_width);
				}
				else
				{
					DPoint mouse_position = (direction == Direction::Horizontal)?
						e->Location:
						DPoint(e->Location.Y, m_scroller_panel->ClientSize.Width-e->Location.X);

 					if(m_scroller_rect_tr.Contains(mouse_position))
					{
						m_is_over_scroller				= true;
						m_is_over_r_scale				= false;
						m_is_over_l_scale				= false;

						if(m_scroller_rect_tr.X+Math::Min(6, m_scroller_rect_tr.Width/3)>=mouse_location){
							m_is_over_l_scale			= true;
							m_scroller_panel->Cursor	= (m_direction == Direction::Horizontal)?
								Windows::Forms::Cursors::SizeWE:
								Windows::Forms::Cursors::SizeNS;
						}
						else if(m_scroller_rect_tr.Right-Math::Min(6, m_scroller_rect_tr.Width/3)<=mouse_location){
							m_is_over_r_scale			= true;
							m_scroller_panel->Cursor	= (m_direction == Direction::Horizontal)?
								Windows::Forms::Cursors::SizeWE:
								Windows::Forms::Cursors::SizeNS;
						}
						else
							m_scroller_panel->Cursor	= Windows::Forms::Cursors::Default;
					}
					else
					{
						m_scroller_panel->Cursor	= Windows::Forms::Cursors::Default;
						m_is_over_scroller			= false;
						m_is_over_l_scale			= false;
						m_is_over_r_scale			= false;
					}
				}

				m_last_mouse_pos = mouse_location;
				m_scroller_panel->Invalidate();
			}

			void		scalable_scroll_bar::m_scroller_panel_MouseDown		(System::Object^ , System::Windows::Forms::MouseEventArgs^  e)
			{
				Int32 mouse_position = transform_mouse(e->Location);

				if(m_is_over_scroller)
				{
					if		(m_is_over_l_scale)		m_is_l_scale_cached		= true;
					else if	(m_is_over_r_scale)		m_is_r_scale_cached		= true;
					else							m_is_scroller_cached	= true;

					m_delta_mouse_to_scroller_pos	= mouse_position-m_scroller_rect_tr.X;
					m_delta_mouse_to_scroller_r_pos = m_scroller_rect_tr.Right - mouse_position;
				}
				else
				{
					m_is_over_scroller		= true;
					scroller_position		= (mouse_position-m_scroller_rect_tr.Width/2)/m_scale_factor+m_scroll_min;
				}
			}

			void		scalable_scroll_bar::m_scroller_panel_MouseUp		(System::Object^ , System::Windows::Forms::MouseEventArgs^ )
			{
				m_is_scroller_cached		= false;
				m_is_r_scale_cached			= false;
				m_is_l_scale_cached			= false;
			}

			void		scalable_scroll_bar::m_scroller_panel_Paint			(System::Object^ , System::Windows::Forms::PaintEventArgs^  e)
			{
				on_draw_background(this, e);

				e->Graphics->Transform		= (m_direction == Direction::Horizontal)?
					gcnew Drawing2D::Matrix(1, 0, 0, 1, 0, 0):
					gcnew Drawing2D::Matrix(0, 1, 1, 0, 0, 0);

				Int32 scroller_width		= m_scroller_rect_tr.Width;
				Int32 scroller_height		= m_scroller_rect_tr.Height;
				Int32 scroller_position		= m_scroller_rect_tr.Location.X;
				Int32 panel_width;
			
				panel_width					= (m_direction == Direction::Horizontal)?
					m_scroller_panel->ClientSize.Width:
					m_scroller_panel->ClientSize.Height;

				Int32 scroller_middle		= scroller_position+scroller_width/2;
				Int32 scroller_left			= scroller_position;
				Int32 scroller_right		= scroller_left+scroller_width;

				if(m_is_over_scrollbar && !m_is_over_scroller)
				{
					Drawing::Rectangle alpha_rect	= m_scroller_rect_tr;
					
					alpha_rect.Location			= Drawing::Point(m_last_mouse_pos-alpha_rect.Width/2, alpha_rect.Y);
							
					if(alpha_rect.X < 1)		
						alpha_rect.Location		= Drawing::Point(1,alpha_rect.Y);
					if(alpha_rect.X+alpha_rect.Width > panel_width-2)
						alpha_rect.Location		= Drawing::Point(panel_width-alpha_rect.Width-2,alpha_rect.Y);
				
					e->Graphics->FillRectangle	(m_alpha_scroller_brush, alpha_rect);
					e->Graphics->DrawRectangle	(m_alpha_scroller_pen, alpha_rect);
				}

				e->Graphics->FillRectangle	((m_is_over_scroller)?m_scroller_brush_active:m_scroller_brush, m_scroller_rect_tr);
				e->Graphics->DrawRectangle	(m_scroller_pen, m_scroller_rect_tr);

				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_middle, 5),	DPoint(scroller_middle, scroller_height-4));
				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_middle+3, 8),	DPoint(scroller_middle+3, scroller_height-7));
				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_middle-3, 8),	DPoint(scroller_middle-3, scroller_height-7));

				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_left+2, 5),	DPoint(scroller_left+2, scroller_height-4));
				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_left+4, 7),	DPoint(scroller_left+4, scroller_height-6));

				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_right-2, 5),	DPoint(scroller_right-2, scroller_height-4));
				e->Graphics->DrawLine		(m_scroller_pen, DPoint(scroller_right-4, 7),	DPoint(scroller_right-4, scroller_height-6));
			}
		}//namespace controls
	}//namespace editor
}//namespace vostok