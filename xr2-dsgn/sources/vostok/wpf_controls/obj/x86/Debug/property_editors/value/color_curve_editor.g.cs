﻿#pragma checksum "..\..\..\..\..\property_editors\value\color_curve_editor.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "5BB20CB1F253B7BC99EC854D5F967EF6"
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
using vostok.editor.wpf_controls.property_editors.item;
using vostok.editor.wpf_controls.property_editors.value;


namespace vostok.editor.wpf_controls.property_editors.value {
    
    
    /// <summary>
    /// color_curve_editor
    /// </summary>
    public partial class color_curve_editor : vostok.editor.wpf_controls.property_editors.value.value_editor_base, System.Windows.Markup.IComponentConnector {
        
        
        #line 6 "..\..\..\..\..\property_editors\value\color_curve_editor.xaml"
        internal vostok.editor.wpf_controls.ruler m_ruler;
        
        #line default
        #line hidden
        
        
        #line 7 "..\..\..\..\..\property_editors\value\color_curve_editor.xaml"
        internal vostok.editor.wpf_controls.color_ramp m_color_ramp;
        
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
            System.Uri resourceLocater = new System.Uri("/wpf_controls;component/property_editors/value/color_curve_editor.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\..\property_editors\value\color_curve_editor.xaml"
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
            this.m_ruler = ((vostok.editor.wpf_controls.ruler)(target));
            return;
            case 2:
            this.m_color_ramp = ((vostok.editor.wpf_controls.color_ramp)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

