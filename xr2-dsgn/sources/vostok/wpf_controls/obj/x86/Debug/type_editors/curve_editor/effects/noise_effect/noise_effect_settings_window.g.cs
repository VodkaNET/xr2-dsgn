﻿#pragma checksum "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "2F4A19D18B4C820BF592A32EDF646ECE"
//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан программой.
//     Исполняемая версия:2.0.50727.9164
//
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторной генерации кода.
// </auto-generated>
//------------------------------------------------------------------------------

using Microsoft.Windows.Themes;
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
using vostok.editor.wpf_controls.property_editors.value;
using vostok.editor.wpf_controls.type_editors;


namespace vostok.editor.wpf_controls.curve_editor.effects {
    
    
    /// <summary>
    /// noise_effect_settings_window
    /// </summary>
    public partial class noise_effect_settings_window : System.Windows.Controls.ContentControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 26 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
        internal vostok.editor.wpf_controls.type_editors.number_editor m_ceed_number_editor;
        
        #line default
        #line hidden
        
        
        #line 31 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
        internal vostok.editor.wpf_controls.type_editors.number_editor m_frequency_number_editor;
        
        #line default
        #line hidden
        
        
        #line 36 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
        internal vostok.editor.wpf_controls.type_editors.number_editor m_strength_number_editor;
        
        #line default
        #line hidden
        
        
        #line 43 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
        internal vostok.editor.wpf_controls.type_editors.number_editor m_fade_in_number_editor;
        
        #line default
        #line hidden
        
        
        #line 50 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
        internal vostok.editor.wpf_controls.type_editors.number_editor m_fade_out_number_editor;
        
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
            System.Uri resourceLocater = new System.Uri("/wpf_controls;component/type_editors/curve_editor/effects/noise_effect/noise_effe" +
                    "ct_settings_window.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
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
            
            #line 9 "..\..\..\..\..\..\..\type_editors\curve_editor\effects\noise_effect\noise_effect_settings_window.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.done_click);
            
            #line default
            #line hidden
            return;
            case 2:
            this.m_ceed_number_editor = ((vostok.editor.wpf_controls.type_editors.number_editor)(target));
            return;
            case 3:
            this.m_frequency_number_editor = ((vostok.editor.wpf_controls.type_editors.number_editor)(target));
            return;
            case 4:
            this.m_strength_number_editor = ((vostok.editor.wpf_controls.type_editors.number_editor)(target));
            return;
            case 5:
            this.m_fade_in_number_editor = ((vostok.editor.wpf_controls.type_editors.number_editor)(target));
            return;
            case 6:
            this.m_fade_out_number_editor = ((vostok.editor.wpf_controls.type_editors.number_editor)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

