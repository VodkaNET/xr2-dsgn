   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullG(clr-namespace:vostok.editor.wpf_controlsvostok.editor.wpf_controls  5      ]3clr-namespace:vostok.editor.wpf_controls.converters%vostok.editor.wpf_controls.converters  6<   ,    &vostok.editor.wpf_controls.time_layout   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      8local(clr-namespace:vostok.editor.wpf_controls    5      H
converters3clr-namespace:vostok.editor.wpf_controls.converters    6<   -   5          >�Name$  time_layout_control��5   �    � 	Resources 5      C   =vostok.editor.wpf_controls.time_layout_item_template_selector &  "time_layout_item_template_selectorK   Evostok.editor.wpf_controls.converters.main_dock_panel_width_converter # main_dock_panel_width_converter ! time_layout_item_template_odd9   3vostok.editor.wpf_controls.time_layout_item_control " time_layout_item_template_even��%�   &	        &	      &	 &     &	 ^       5   
   63     5   
   6:   �� 5   
   .R�5	        
�������6-   5
      �� 5   
   .R�5        
�������6-   5      5      .��5      �� -   5         ��Name$ horizontal_scroll��5      $��Hidden=�6.   $��Disabled=�6U   .��5   
   ]� -   5         ]�Name$ main_dock_panel��5      
�������$
��Left=�6C   ��. ��5      `� 5       `� 	Converter# [ 6   .1�5      ��  �� ElementName$ parent_node_panel��6    �� Path$ Width�6>   6M   �� 5      $ time_layout_control��6   $ ActualWidth�6@   6U   5      .+�5      ]� -   5        $ parent_node_panel��5   J   
�����_�$
��Left=�6/   $	��Top=�5      ��. .+�5      �� $��0��6    �� TextAlignment$
 Left=�6"   $
��Left=�67   $��Center=�6M   6l   >� 5      -   5        $(  "parent_node_time_layout_right_edge��5   .    � Cursor$ SizeWE��6   $��Right=�6Z   $��10��6q   
������ 6�   �� 5      -   5        	 ��Name$	 parent_length��5      $��0q�61   
������ $��Right=�6^   
 �� TextAlignment$
 Right=�6u   6  �� 5      $ Center=�6_   ��6   �� $ time_layout_control��$ parent_text�6_   5       &    vostok.editor.wpf_controls.ruler  5!      -   5          Name$ time_layout_ruler��5!       J� SnapsToDevicePixels . $��20��6P   $��Bottom=�6\   �� 5"      $��Hidden=�6   $��Disabled=�6@   .��5#      � -   5        $��items_grid_panel��5#      .+�5$      ��  K� ZIndex$ 5��6   .+�5%      F� -	   5        $��selection_path��5%      
���   � �� StrokeDashArray$
 3, 2R�62   $��1��6I    . 6]   5&      �� 5'      -
   5         ��Name$ items��5'      #��[  6#   5)      5*      5+      5,      5-      5.      