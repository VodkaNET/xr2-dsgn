   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nulla5clr-namespace:vostok.editor.wpf_controls.curve_editor'vostok.editor.wpf_controls.curve_editor  5      ]3clr-namespace:vostok.editor.wpf_controls.converters%vostok.editor.wpf_controls.converters  5      G(clr-namespace:vostok.editor.wpf_controlsvostok.editor.wpf_controls  5      @    :vostok.editor.wpf_controls.curve_editor.curve_editor_panel   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      Lcurve_editor5clr-namespace:vostok.editor.wpf_controls.curve_editor    5      H
converters3clr-namespace:vostok.editor.wpf_controls.converters    5      ?wpf_controls(clr-namespace:vostok.editor.wpf_controls    5      -   5        $
��this��5	      &    vostok.editor.wpf_controls.input    PreviewInputCommand  handle_input5
      |�.  � 	Resources 5         key_context_menu �� 
TargetType �� Property �� ValueH  Bvostok.editor.wpf_controls.converters.bool_to_visibility_converter  direct_visibility_converter   reverse_visibility_converter   
do_reverse��%�  &	        '�� W    &	 �    &	 �    �� 5      .@�5      m� $��Tangents��6   .@�5      m� -   5        $��Linear��5      6!   m� 5      -   5        $��Spline Auto��5      6%   m� 5      -   5        $��Spline Manual��5      6&   m� 5      -   5        $��Breaked��5      6"   �� 5      m� 5      -   5        $
��Flat��5      6    5      m� 5      $
��View��6   .@�5      m� -   5        $��	Focus All��5      6$   m� 5      -   5        $��Focus Default Range��5      6,   5      m� 5      -	   5        $��
Remove Key��5      6"   5      �� 5      " ��6
   .�5      ��  � ��$ 24��6   5        5      6,     5       . 6Q   5       .��5!      �� 
���   �$��1q�6   ._�5"      ]� .+�5#      �� $	��Top=�6   $��
0, 0, 0, 1q�6!   
���   �y�6R   �� *is_toolbar_visible+ �� ElementName$
 this�� �� 	Converter# [ ._�5$      c� -
   5         J� SnapsToDevicePixels . .@�5%      	� -   5        $��m_move_tool_button��5%      	 d� 	IsChecked$
	 TrueY�6-   
 � ToolTip$
 	Move Tool��6>   .��6S   �� $��icons/movenodes.png��6Y   6z   	� 5&      -   5        $��m_scale_tool_button��5&      $
 
Scale Tool��6.   .��6D   �� $��icons/scalenodes.png��6J   6l   	� 5'      -   5        $��m_move_range_tool_button��5'      $
 Move Range Tool��63   .��6N   �� $��icons/moverange.png��6T   6u   	� 5(      -   5        $��m_add_tool_button��5(      $
 Add Tool��6,   .��6@   �� $��icons/addkey.png��6F   6d   	� 5)      -   5        $��m_remove_tool_button��5)      $
 Remove Tool��6/   .��6F   �� $��icons/removekey.png��6L   6m   �� 5*      d� 5+      -   5        $��m_snap_to_point_toggle��5+      $
 Toggle Snap To Point��62   .��6R   �� $��icons/snaptonodes.png��6X   6{   d� 5,      -   5        $��m_snap_to_grid_toggle��5,      $
 Toggle Snap To Grid��61   .��6P   �� $��icons/snaptogrid.png��6V   6x   �� 5-      �� 5.      -   5        $��m_key_type_buttons��5.   +    �� Orientation$ 
Horizontal=�6    5/       �� BasedOn��%�   '��       7 �'d�      7�'�� :     7��� 50   	   8   " ��6L   �� 51   	   8   " d�6R   �� 52   	   8   " ��6M   53   	   .+�55      �� $��X:��6   $��Center=�6   �� 56      |�. ._�57   	   �� -   5        $ ��m_keys_x_position_text_box��57      $��60��6M   6�   58   	   �� 59      $��Y:��6   $��Center=�6   �� 5:      |�. -  'System.Windows.Input.KeyboardNavigation   TabNavigation$ Local=�6    ._�5;   	   �� -   5        $ ��m_keys_y_position_text_box��5;      $��60��6M   6�   5<   	   �� 5=      d� 5>      -   5        $��m_toggle_range_button��5>      {�.  $
 Toggle Range��6�   .��5?   	   � .+�5@   
   �� $��icons/togglerange1.png��6   $��24��6�   y�60   �� *	IsChecked+$ m_toggle_range_button��# [ 6�   �� 5A   
   $��icons/togglerange0.png��6   $��24��6�   y�60   �� *	IsChecked+$ m_toggle_range_button��# [ 6�   5B   
   5C   	   �� 5D      d� 5E      -   5        $��m_linked_auto_button��5E   /   {�.  $
 Make Linked Auto��6]   .��6y   �� $��icons/nodetype1.png��6   6�   d� 5F      -   5        $��m_linear_button��5F   *   {�.  $
 Make Linear��6S   .��6j   �� $��icons/nodetype2.png��6p   6�   d� 5G      -   5        $��m_step_button��5G   (   {�.  $
 	Make Step��6O   .��6d   �� $��icons/nodetype3.png��6j   {�. 6�   6�   d� 5H      -   5        $��m_linked_manual_button��5H   1   {�.  $
 Make Linked Manual��6b   .��6�   �� $��icons/nodetype4.png��6�   6�   d� 5I      -   5        $��m_breaked_button��5I   +   {�.  $
 Make Breaked��6U   .��6m   �� $��icons/nodetype5.png��6s   6�   5J      �� 5K      �� 5L      -   5        $
 Focus��5L   "   .��63   �� $��icons/focus.png��69   6U   �� 5M      -   5        $��m_focus_range_button��5M   N   $
 Focus Default Range��60   .��6k   �� $#��icons/focustodefaultrange.png��6q   6�   �� 5N      o� 5O      $��Center=�6   .@�5P      m� -   5        $��m_set_template_menu_item��5P   &   $��SetTemplate��6   .@�5Q   	   m� -   5        $��Sinusoid��5Q      6$   m� 5R   	   -   5        $
��Sqrt��5R      6    �� 5S   	   5T   	   5U      5V      5W      �� 5X      $
��Left=�6   $��
0, 0, 1, 0q�6"   
���   �y�6S   �� *is_hierarchy_visible+$
 this��# [ ._�5Y      �� -    5        $��m_curves_groups��5Y      
������  � FocusVisualStyle 6*   Z� 6j   5Z      �� 5[      $��Bottom=�6   ._�5\      �� -!   5        $��m_curves_scroll_bar��5\       �� Orientation$ 
Horizontal=�6+   $y�	Collapsed=�6l   $��20��6�   6�   5]      �� 5^      -"   5        $��m_decorator_panel��5^      .��5_      :  4vostok.editor.wpf_controls.curve_editor.curves_panel  -#   5          Name$ m_curves_panel��5_       :   4vostok.editor.wpf_controls.curve_editor.curves_panel   	MouseDown$ 
mouse_down��5`         	MouseMove$ 
mouse_move��5a         MouseUp$ mouse_up��5b         PreviewMouseDown$ preview_mouse_down��5c         SizeChanged$ size_changed��5d       . $��20��5_   S   $��10��6a   5d      5e      5f      5g      5h      