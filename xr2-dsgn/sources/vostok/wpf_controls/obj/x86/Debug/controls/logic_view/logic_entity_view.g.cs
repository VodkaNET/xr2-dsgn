﻿#pragma checksum "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "B53541C342D1EDE5BEDC81F2BC8F4322"
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
using vostok.editor.wpf_controls.hypergraph;


namespace vostok.editor.wpf_controls.logic_view {
    
    
    /// <summary>
    /// logic_entity_view
    /// </summary>
    public partial class logic_entity_view : System.Windows.Controls.Border, System.Windows.Markup.IComponentConnector {
        
        
        #line 1 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        internal vostok.editor.wpf_controls.logic_view.logic_entity_view parent_control;
        
        #line default
        #line hidden
        
        
        #line 23 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        internal System.Windows.Controls.Primitives.Thumb bottom_grip;
        
        #line default
        #line hidden
        
        
        #line 32 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        internal System.Windows.Controls.Border logic_entity_resource_top;
        
        #line default
        #line hidden
        
        /// <summary>
        /// item_text Name Field
        /// </summary>
        
        #line 33 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        public System.Windows.Controls.TextBlock item_text;
        
        #line default
        #line hidden
        
        /// <summary>
        /// start_event_combobox Name Field
        /// </summary>
        
        #line 43 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        public System.Windows.Controls.ComboBox start_event_combobox;
        
        #line default
        #line hidden
        
        /// <summary>
        /// logic_entity_resource_button Name Field
        /// </summary>
        
        #line 47 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        public System.Windows.Controls.Button logic_entity_resource_button;
        
        #line default
        #line hidden
        
        /// <summary>
        /// logic_entity_resource_button_border Name Field
        /// </summary>
        
        #line 48 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        public System.Windows.Controls.Border logic_entity_resource_button_border;
        
        #line default
        #line hidden
        
        /// <summary>
        /// selected_resource Name Field
        /// </summary>
        
        #line 49 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        public System.Windows.Controls.TextBlock selected_resource;
        
        #line default
        #line hidden
        
        /// <summary>
        /// logic_hypergraph Name Field
        /// </summary>
        
        #line 55 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
        public vostok.editor.wpf_controls.hypergraph.hypergraph_control logic_hypergraph;
        
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
            System.Uri resourceLocater = new System.Uri("/wpf_controls;component/controls/logic_view/logic_entity_view.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
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
            this.parent_control = ((vostok.editor.wpf_controls.logic_view.logic_entity_view)(target));
            
            #line 8 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            this.parent_control.PreviewMouseLeftButtonDown += new System.Windows.Input.MouseButtonEventHandler(this.parent_control_mouse_left_button_down);
            
            #line default
            #line hidden
            return;
            case 2:
            this.bottom_grip = ((System.Windows.Controls.Primitives.Thumb)(target));
            
            #line 23 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            this.bottom_grip.DragDelta += new System.Windows.Controls.Primitives.DragDeltaEventHandler(this.on_bottom_drag);
            
            #line default
            #line hidden
            return;
            case 3:
            this.logic_entity_resource_top = ((System.Windows.Controls.Border)(target));
            return;
            case 4:
            this.item_text = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 5:
            
            #line 36 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.on_add_behaviour_button_clicked);
            
            #line default
            #line hidden
            return;
            case 6:
            this.start_event_combobox = ((System.Windows.Controls.ComboBox)(target));
            
            #line 43 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            this.start_event_combobox.PreviewMouseDown += new System.Windows.Input.MouseButtonEventHandler(this.on_start_event_combo_box_down);
            
            #line default
            #line hidden
            
            #line 43 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            this.start_event_combobox.DropDownClosed += new System.EventHandler(this.start_event_combo_box_drop_down_closed);
            
            #line default
            #line hidden
            
            #line 43 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            this.start_event_combobox.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.on_start_event_combobox_selection_changed);
            
            #line default
            #line hidden
            return;
            case 7:
            this.logic_entity_resource_button = ((System.Windows.Controls.Button)(target));
            
            #line 47 "..\..\..\..\..\controls\logic_view\logic_entity_view.xaml"
            this.logic_entity_resource_button.Click += new System.Windows.RoutedEventHandler(this.on_select_object_button_clicked);
            
            #line default
            #line hidden
            return;
            case 8:
            this.logic_entity_resource_button_border = ((System.Windows.Controls.Border)(target));
            return;
            case 9:
            this.selected_resource = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 10:
            this.logic_hypergraph = ((vostok.editor.wpf_controls.hypergraph.hypergraph_control)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

