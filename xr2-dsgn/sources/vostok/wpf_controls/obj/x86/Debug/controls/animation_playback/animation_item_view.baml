   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]3clr-namespace:vostok.editor.wpf_controls.converters%vostok.editor.wpf_controls.converters  5      G    Avostok.editor.wpf_controls.animation_playback.animation_item_view   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      H
converters3clr-namespace:vostok.editor.wpf_controls.converters    5      
�������$��1q�5      
���   �  J� SnapsToDevicePixels  .  � 	Resources 5      I  Cvostok.editor.wpf_controls.converters.single_to_thickness_converter   left_converterJ  Dvostok.editor.wpf_controls.converters.singles_to_thickness_converter  multi_converter��%:   &	        &	        5      6-     5      6.   5	      .��5      �� ��6
   �� *height+._�5      � .+�5      �� $
��Left=�6   $��1q�6I   
���   �
���  ����60   �� *offset+��6�   �� *bindings.weighted_height+��5      `� 5       `� 	Converter# [ 6#   1�5      �� 5       �� Path$ position�6&   �� 5      $ bindings.top_offset�6&   5      5      �� 5      $
��Left=�6   $��1q�6W   
���   �
��� �����6'   �� *bindings.animation_time_width+��6�   �� *bindings.weighted_height+��5      `� 5      # [ 6#   1�5      �� 5      $ bindings.offset_position�6&   �� 5      $ bindings.top_offset�6&   5      5       �� 5!      $
��Left=�6   $��1q�6U   
���   �
����  ���6'   �� *bindings.time_scaled_length+��6�   �� *bindings.weighted_height+��5"      `� 5#      # [ 6   1�5$      �� 5%   	   $ bindings.animation_time�6   �� 5&   	   $ bindings.top_offset�6   5(      5*      �� 5+      $
��Left=�6   $��2q�6�   
���   �
������ ��6'   �� *
position+ �� 	Converter# [  ��6n   �� *length+��6�   �� *height+�� 5,       K� ZIndex$	 100��61   ��6   �� *events+��5-      �� 5.      .R�5/      � 50      ��52      �� 53      .R�54      � $��20��6   $��20��6   $
��Left=�6$   $��Center=�6?   ��6Z   �� *
position+# [  .+�55   	   F� $��Bottom=�6   "�������     � -1 -1�     -1	
������
���   �$��1��6g   �� 56   	   $��Center=�6)   $��Center=�6D   $��0, 0, 0, -8q�6a   ��6   �� *text+6a   57   	   58      5:      F� 5;      
���  ��$��1��6   $	 150��6+   ��5<      B� 5=      -   5        m_weights_curves��5=      5?      F� 5@      
��� � �$��1��6   $	 150��6-   ��5A      B� 5B      -   5        m_scales_curves��5B      5D      F� 5E      
�������$��1��6   $	 150��61   ��5F      B� 5G      -   5        m_weights_levels��5G      5I      F� 5J      
������$��1��6   $	 150��62   ��5K      B� 5L      -   5        m_scales_levels��5L      5N      5O      5P      5Q      