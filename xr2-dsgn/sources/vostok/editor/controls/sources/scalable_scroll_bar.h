////////////////////////////////////////////////////////////////////////////
//	Created		: 16.01.2010
//	Author		: Evgeniy Obertyukh
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef SCALABLE_SCROLL_BAR_H_INCLUDED
#define SCALABLE_SCROLL_BAR_H_INCLUDED

#include "scroller_event_args.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

typedef	Drawing::Point DPoint;

namespace vostok
{
	namespace editor
	{
		namespace controls
		{
			/// <summary>
			/// Summary for scalable_scroll_bar
			/// </summary>
			public ref class scalable_scroll_bar : public System::Windows::Forms::UserControl
			{
			
			#pragma region | InnerTypes |

			public:
				enum class Direction
				{
					Horizontal,
					Vertical
				};

			#pragma endregion

			#pragma region |   Events   |

			public:
				event EventHandler<scroller_event_args^>^		scroller_moved;
				event PaintEventHandler^						on_draw_background;

			#pragma endregion

			#pragma region | Initialize |
			
			public:
				scalable_scroll_bar(void):
					c_min_scroller_width	(12),
					m_scroll_min			(0),
					m_scroll_max			(100),
					m_scroller_width		(20),
					m_scroller_position		(25)
				{
					InitializeComponent();
					//
					//TODO: Add the constructor code here
					//
					in_constructor();
				}

			protected:
				/// <summary>
				/// Clean up any resources being used.
				/// </summary>
				~scalable_scroll_bar()
				{
					if (components)
					{
						delete components;
					}
				}
			private: System::Windows::Forms::Button^  m_move_left_button;
			private: System::Windows::Forms::Button^  m_move_right_button;
			protected: 

			protected: 

			private: System::Windows::Forms::Panel^  m_right_button_slot_panel;

			private: System::Windows::Forms::Panel^  m_left_button_slot_panel;
			private: System::Windows::Forms::Panel^  m_scroller_panel;




			private:
				void in_constructor();
				/// <summary>
				/// Required designer variable.
				/// </summary>
				System::ComponentModel::Container ^components;

			#pragma region Windows Form Designer generated code
				/// <summary>
				/// Required method for Designer support - do not modify
				/// the contents of this method with the code editor.
				/// </summary>
				void InitializeComponent(void)
				{
					this->m_move_left_button = (gcnew System::Windows::Forms::Button());
					this->m_move_right_button = (gcnew System::Windows::Forms::Button());
					this->m_right_button_slot_panel = (gcnew System::Windows::Forms::Panel());
					this->m_left_button_slot_panel = (gcnew System::Windows::Forms::Panel());
					this->m_scroller_panel = (gcnew System::Windows::Forms::Panel());
					this->SuspendLayout();
					// 
					// m_move_left_button
					// 
					this->m_move_left_button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
					this->m_move_left_button->Dock = System::Windows::Forms::DockStyle::Left;
					this->m_move_left_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
					this->m_move_left_button->Font = (gcnew System::Drawing::Font(L"Microsoft Uighur", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel, 
						static_cast<System::Byte>(204)));
					this->m_move_left_button->Location = System::Drawing::Point(0, 0);
					this->m_move_left_button->Name = L"m_move_left_button";
					this->m_move_left_button->Size = System::Drawing::Size(20, 23);
					this->m_move_left_button->TabIndex = 0;
					this->m_move_left_button->Text = L"◄";
					this->m_move_left_button->UseVisualStyleBackColor = false;
					this->m_move_left_button->Click += gcnew System::EventHandler(this, &scalable_scroll_bar::m_move_left_button_Click);
					// 
					// m_move_right_button
					// 
					this->m_move_right_button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
					this->m_move_right_button->Dock = System::Windows::Forms::DockStyle::Right;
					this->m_move_right_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
					this->m_move_right_button->Font = (gcnew System::Drawing::Font(L"Microsoft Uighur", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel, 
						static_cast<System::Byte>(204)));
					this->m_move_right_button->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->m_move_right_button->Location = System::Drawing::Point(400, 0);
					this->m_move_right_button->Name = L"m_move_right_button";
					this->m_move_right_button->Size = System::Drawing::Size(20, 23);
					this->m_move_right_button->TabIndex = 0;
					this->m_move_right_button->Text = L"►";
					this->m_move_right_button->UseVisualStyleBackColor = false;
					this->m_move_right_button->Click += gcnew System::EventHandler(this, &scalable_scroll_bar::m_move_right_button_Click);
					// 
					// m_right_button_slot_panel
					// 
					this->m_right_button_slot_panel->Dock = System::Windows::Forms::DockStyle::Right;
					this->m_right_button_slot_panel->Location = System::Drawing::Point(420, 0);
					this->m_right_button_slot_panel->Name = L"m_right_button_slot_panel";
					this->m_right_button_slot_panel->Size = System::Drawing::Size(0, 23);
					this->m_right_button_slot_panel->TabIndex = 1;
					// 
					// m_left_button_slot_panel
					// 
					this->m_left_button_slot_panel->Dock = System::Windows::Forms::DockStyle::Left;
					this->m_left_button_slot_panel->Location = System::Drawing::Point(0, 0);
					this->m_left_button_slot_panel->Name = L"m_left_button_slot_panel";
					this->m_left_button_slot_panel->Size = System::Drawing::Size(0, 23);
					this->m_left_button_slot_panel->TabIndex = 1;
					// 
					// m_scroller_panel
					// 
					this->m_scroller_panel->BackColor = System::Drawing::SystemColors::Control;
					this->m_scroller_panel->Dock = System::Windows::Forms::DockStyle::Fill;
					this->m_scroller_panel->Location = System::Drawing::Point(20, 0);
					this->m_scroller_panel->Name = L"m_scroller_panel";
					this->m_scroller_panel->Size = System::Drawing::Size(380, 23);
					this->m_scroller_panel->TabIndex = 1;
					this->m_scroller_panel->MouseLeave += gcnew System::EventHandler(this, &scalable_scroll_bar::m_scroller_panel_MouseLeave);
					this->m_scroller_panel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &scalable_scroll_bar::m_scroller_panel_Paint);
					this->m_scroller_panel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &scalable_scroll_bar::m_scroller_panel_MouseMove);
					this->m_scroller_panel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &scalable_scroll_bar::m_scroller_panel_MouseDown);
					this->m_scroller_panel->Resize += gcnew System::EventHandler(this, &scalable_scroll_bar::m_scroller_panel_Resize);
					this->m_scroller_panel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &scalable_scroll_bar::m_scroller_panel_MouseUp);
					this->m_scroller_panel->MouseEnter += gcnew System::EventHandler(this, &scalable_scroll_bar::m_scroller_panel_MouseEnter);
					// 
					// scalable_scroll_bar
					// 
					this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
					this->Controls->Add(this->m_scroller_panel);
					this->Controls->Add(this->m_move_right_button);
					this->Controls->Add(this->m_move_left_button);
					this->Controls->Add(this->m_left_button_slot_panel);
					this->Controls->Add(this->m_right_button_slot_panel);
					this->Name = L"scalable_scroll_bar";
					this->Size = System::Drawing::Size(420, 23);
					this->VisibleChanged += gcnew System::EventHandler(this, &scalable_scroll_bar::scalable_scroll_bar_VisibleChanged);
					this->ResumeLayout(false);

				}
			#pragma endregion

			#pragma endregion 

			#pragma region |   Fields   |

			private:
				const Int32	c_min_scroller_width;

				Direction	m_direction;

				Single		m_scroll_min;
				Single		m_scroll_max;
				Single		m_scroller_position;
				Single		m_scroller_width;
				Single		m_scale_factor;
				Pen^		m_scroller_pen;
				Brush^		m_scroller_brush;
				Brush^		m_scroller_brush_active;
				Pen^		m_alpha_scroller_pen;
				Brush^		m_alpha_scroller_brush;

				Boolean 	m_is_over_scroller;
				Boolean 	m_is_over_scrollbar;
				Boolean 	m_is_over_l_scale;
				Boolean 	m_is_over_r_scale;
				Boolean 	m_is_scroller_cached;
				Boolean 	m_is_l_scale_cached;
				Boolean 	m_is_r_scale_cached;

				Int32		m_last_mouse_pos;
				Int32		m_delta_mouse_to_scroller_pos;
				Int32		m_delta_mouse_to_scroller_r_pos;

				Drawing::Rectangle	m_scroller_rect_tr;

			#pragma endregion 

			#pragma region | Properties |

			public:
				property Direction	direction
				{
					Direction	get(){return m_direction;};
					void		set(Direction value);
				}
				property Single		scroller_position
				{
					Single		get(){return m_scroller_position;};
					void		set(Single value);
				}
				property Single		scroll_min
				{
					Single		get(){return m_scroll_min;};
					void		set(Single value){m_scroll_min=value;compute_values_on_scale();};
				}
				property Single		scroll_max
				{
					Single		get(){return m_scroll_max;};
					void		set(Single value){m_scroll_max=value;compute_values_on_scale();};
				}
				property Single		scroller_width
				{
					Single		get(){return m_scroller_width;};
					void		set(Single value){m_scroller_width=value;compute_values_on_scale();};
				}
				[BrowsableAttribute(false)]
				property Panel^		scroller_panel
				{
					Panel^		get(){return m_scroller_panel;};
				}

			#pragma endregion 

			#pragma region |  Methods   |
			
			private:
				void	compute_values_on_scale			();
				Int32	transform_mouse					(DPoint mouse_pos);

				void	scalable_scroll_bar_VisibleChanged	(System::Object^  sender, System::EventArgs^  e);
				void 	m_scroller_panel_Resize			(System::Object^  sender, System::EventArgs^  e);
				void 	m_move_left_button_Click		(System::Object^  sender, System::EventArgs^  e);
				void 	m_move_right_button_Click		(System::Object^  sender, System::EventArgs^  e);
				void 	m_scroller_panel_MouseLeave		(System::Object^  sender, System::EventArgs^  e);
				void 	m_scroller_panel_MouseEnter		(System::Object^  sender, System::EventArgs^  e);
				void 	m_scroller_panel_MouseMove		(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
				void 	m_scroller_panel_MouseDown		(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
				void 	m_scroller_panel_MouseUp		(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
				void 	m_scroller_panel_Paint			(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

			public:
				void 	set_scroller					(Single set_position, Single set_width);
				void 	set_scroller					(Single set_position, Single set_width, Boolean need_send_message);
				void 	set_scrollbar					(Single scroll_min, Single scroll_max, Single set_position, Single set_width);
				void 	set_scrollbar					(Single scroll_min, Single scroll_max, Single set_position, Single set_width, Boolean need_send_message);

			#pragma endregion 

			};//class scalable_scroll_bar
		}//namespace controls
	}//namespace editor
}//namespace vostok
#endif // #ifndef SCALABLE_SCROLL_BAR_H_INCLUDED