﻿#pragma checksum "..\..\..\..\..\type_editors\curve_editor\panel_curve_effect.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "F97DF05617FA1A1565D1D0B4D19FD7EC"
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


namespace vostok.editor.wpf_controls.curve_editor {
    
    
    /// <summary>
    /// panel_curve_effect
    /// </summary>
    public partial class panel_curve_effect : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 11 "..\..\..\..\..\type_editors\curve_editor\panel_curve_effect.xaml"
        private System.Windows.Controls.TextBlock m_text_block;
        
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
            System.Uri resourceLocater = new System.Uri("/wpf_controls;component/type_editors/curve_editor/panel_curve_effect.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\..\type_editors\curve_editor\panel_curve_effect.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            
            #line 5 "..\..\..\..\..\type_editors\curve_editor\panel_curve_effect.xaml"
            ((vostok.editor.wpf_controls.curve_editor.panel_curve_effect)(target)).MouseDown += new System.Windows.Input.MouseButtonEventHandler(this.mouse_down);
            
            #line default
            #line hidden
            return;
            case 2:
            
            #line 8 "..\..\..\..\..\type_editors\curve_editor\panel_curve_effect.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.remove_click);
            
            #line default
            #line hidden
            return;
            case 3:
            this.m_text_block = ((System.Windows.Controls.TextBlock)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

