﻿#pragma checksum "..\..\..\..\..\type_editors\curve_editor\panel.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "6305C8BCD041DDBB2C1696B4DABC90D4"
//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан программой.
//     Исполняемая версия:2.0.50727.9164
//
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторной генерации кода.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms.Integration;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using vostok.editor.wpf_controls;
using vostok.editor.wpf_controls.converters;
using vostok.editor.wpf_controls.curve_editor;


namespace vostok.editor.wpf_controls.curve_editor {
    
    
    /// <summary>
    /// curve_editor_panel
    /// </summary>
    public partial class curve_editor_panel : System.Windows.Controls.ContentControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 9 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal vostok.editor.wpf_controls.curve_editor.curve_editor_panel @this;
        
        #line default
        #line hidden
        
        
        #line 37 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.RadioButton m_move_tool_button;
        
        #line default
        #line hidden
        
        
        #line 38 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.RadioButton m_scale_tool_button;
        
        #line default
        #line hidden
        
        
        #line 39 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.RadioButton m_move_range_tool_button;
        
        #line default
        #line hidden
        
        
        #line 40 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.RadioButton m_add_tool_button;
        
        #line default
        #line hidden
        
        
        #line 41 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.RadioButton m_remove_tool_button;
        
        #line default
        #line hidden
        
        
        #line 43 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_snap_to_point_toggle;
        
        #line default
        #line hidden
        
        
        #line 44 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_snap_to_grid_toggle;
        
        #line default
        #line hidden
        
        
        #line 46 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        private System.Windows.Controls.StackPanel m_key_type_buttons;
        
        #line default
        #line hidden
        
        
        #line 55 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        private System.Windows.Controls.TextBox m_keys_x_position_text_box;
        
        #line default
        #line hidden
        
        
        #line 59 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        private System.Windows.Controls.TextBox m_keys_y_position_text_box;
        
        #line default
        #line hidden
        
        
        #line 62 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        private System.Windows.Controls.Primitives.ToggleButton m_toggle_range_button;
        
        #line default
        #line hidden
        
        
        #line 69 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_linked_auto_button;
        
        #line default
        #line hidden
        
        
        #line 70 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_linear_button;
        
        #line default
        #line hidden
        
        
        #line 71 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_step_button;
        
        #line default
        #line hidden
        
        
        #line 72 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_linked_manual_button;
        
        #line default
        #line hidden
        
        
        #line 73 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ToggleButton m_breaked_button;
        
        #line default
        #line hidden
        
        
        #line 77 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Button m_focus_range_button;
        
        #line default
        #line hidden
        
        
        #line 80 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.MenuItem m_set_template_menu_item;
        
        #line default
        #line hidden
        
        
        #line 89 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.ItemsControl m_curves_groups;
        
        #line default
        #line hidden
        
        
        #line 92 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal System.Windows.Controls.Primitives.ScrollBar m_curves_scroll_bar;
        
        #line default
        #line hidden
        
        
        #line 94 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        private System.Windows.Controls.ContentControl m_decorator_panel;
        
        #line default
        #line hidden
        
        
        #line 95 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
        internal vostok.editor.wpf_controls.curve_editor.curves_panel m_curves_panel;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/wpf_controls;component/type_editors/curve_editor/panel.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal System.Delegate _CreateDelegate(System.Type delegateType, string handler) {
            return System.Delegate.CreateDelegate(delegateType, this, handler);
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.@this = ((vostok.editor.wpf_controls.curve_editor.curve_editor_panel)(target));
            
            #line 8 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.@this.KeyDown += new System.Windows.Input.KeyEventHandler(this.preview_key_down);
            
            #line default
            #line hidden
            return;
            case 2:
            
            #line 14 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.linear_click);
            
            #line default
            #line hidden
            return;
            case 3:
            
            #line 15 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.linked_auto_click);
            
            #line default
            #line hidden
            return;
            case 4:
            
            #line 16 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.linked_manual_click);
            
            #line default
            #line hidden
            return;
            case 5:
            
            #line 17 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.breaked_click);
            
            #line default
            #line hidden
            return;
            case 6:
            
            #line 19 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.step_click);
            
            #line default
            #line hidden
            return;
            case 7:
            
            #line 22 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.focus_click);
            
            #line default
            #line hidden
            return;
            case 8:
            
            #line 23 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.focus_default_range_click);
            
            #line default
            #line hidden
            return;
            case 9:
            
            #line 25 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.remove_menu_item_click);
            
            #line default
            #line hidden
            return;
            case 10:
            
            #line 36 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.ToolBar)(target)).AddHandler(System.Windows.Controls.Primitives.ToggleButton.CheckedEvent, new System.Windows.RoutedEventHandler(this.tool_changed));
            
            #line default
            #line hidden
            return;
            case 11:
            this.m_move_tool_button = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 12:
            this.m_scale_tool_button = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 13:
            this.m_move_range_tool_button = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 14:
            this.m_add_tool_button = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 15:
            this.m_remove_tool_button = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 16:
            this.m_snap_to_point_toggle = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            return;
            case 17:
            this.m_snap_to_grid_toggle = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            return;
            case 18:
            this.m_key_type_buttons = ((System.Windows.Controls.StackPanel)(target));
            return;
            case 19:
            this.m_keys_x_position_text_box = ((System.Windows.Controls.TextBox)(target));
            
            #line 55 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_keys_x_position_text_box.KeyDown += new System.Windows.Input.KeyEventHandler(this.key_x_position_text_box_key_down);
            
            #line default
            #line hidden
            
            #line 55 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_keys_x_position_text_box.LostFocus += new System.Windows.RoutedEventHandler(this.key_x_position_text_box_focus_lost);
            
            #line default
            #line hidden
            return;
            case 20:
            this.m_keys_y_position_text_box = ((System.Windows.Controls.TextBox)(target));
            
            #line 59 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_keys_y_position_text_box.KeyDown += new System.Windows.Input.KeyEventHandler(this.key_y_position_text_box_key_down);
            
            #line default
            #line hidden
            
            #line 59 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_keys_y_position_text_box.LostFocus += new System.Windows.RoutedEventHandler(this.key_y_position_text_box_focus_lost);
            
            #line default
            #line hidden
            return;
            case 21:
            this.m_toggle_range_button = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 62 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_toggle_range_button.Click += new System.Windows.RoutedEventHandler(this.toggle_range_button_click);
            
            #line default
            #line hidden
            return;
            case 22:
            this.m_linked_auto_button = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 69 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_linked_auto_button.Click += new System.Windows.RoutedEventHandler(this.linked_auto_click);
            
            #line default
            #line hidden
            return;
            case 23:
            this.m_linear_button = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 70 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_linear_button.Click += new System.Windows.RoutedEventHandler(this.linear_click);
            
            #line default
            #line hidden
            return;
            case 24:
            this.m_step_button = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 71 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_step_button.Click += new System.Windows.RoutedEventHandler(this.step_click);
            
            #line default
            #line hidden
            return;
            case 25:
            this.m_linked_manual_button = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 72 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_linked_manual_button.Click += new System.Windows.RoutedEventHandler(this.linked_manual_click);
            
            #line default
            #line hidden
            return;
            case 26:
            this.m_breaked_button = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 73 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_breaked_button.Click += new System.Windows.RoutedEventHandler(this.breaked_click);
            
            #line default
            #line hidden
            return;
            case 27:
            
            #line 76 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.focus_click);
            
            #line default
            #line hidden
            return;
            case 28:
            this.m_focus_range_button = ((System.Windows.Controls.Button)(target));
            
            #line 77 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_focus_range_button.Click += new System.Windows.RoutedEventHandler(this.focus_default_range_click);
            
            #line default
            #line hidden
            return;
            case 29:
            this.m_set_template_menu_item = ((System.Windows.Controls.MenuItem)(target));
            return;
            case 30:
            
            #line 81 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.set_sinusoid_template);
            
            #line default
            #line hidden
            return;
            case 31:
            
            #line 82 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            ((System.Windows.Controls.MenuItem)(target)).Click += new System.Windows.RoutedEventHandler(this.set_sqrt_template);
            
            #line default
            #line hidden
            return;
            case 32:
            this.m_curves_groups = ((System.Windows.Controls.ItemsControl)(target));
            
            #line 89 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_curves_groups.MouseDown += new System.Windows.Input.MouseButtonEventHandler(this.groups_panel_mouse_down);
            
            #line default
            #line hidden
            return;
            case 33:
            this.m_curves_scroll_bar = ((System.Windows.Controls.Primitives.ScrollBar)(target));
            
            #line 92 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_curves_scroll_bar.ValueChanged += new System.Windows.RoutedPropertyChangedEventHandler<double>(this.scroll_bar_value_changed);
            
            #line default
            #line hidden
            
            #line 92 "..\..\..\..\..\type_editors\curve_editor\panel.xaml"
            this.m_curves_scroll_bar.SizeChanged += new System.Windows.SizeChangedEventHandler(this.scroll_bar_size_changed);
            
            #line default
            #line hidden
            return;
            case 34:
            this.m_decorator_panel = ((System.Windows.Controls.ContentControl)(target));
            return;
            case 35:
            this.m_curves_panel = ((vostok.editor.wpf_controls.curve_editor.curves_panel)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

