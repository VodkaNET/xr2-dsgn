   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]3clr-namespace:vostok.editor.wpf_controls.logic_view%vostok.editor.wpf_controls.logic_view  5   <   9    3vostok.editor.wpf_controls.logic_view.event_control   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      H
logic_view3clr-namespace:vostok.editor.wpf_controls.logic_view    6<   -   5          n�Name$  parent_control��5       � Cursor$ SizeWE��5       � ContextMenu 5      �� 5	      -   5        $��m_context_menu��5	      .@�5
      m� -   5        $��cm_delete_selected_events��5
      $��Delete selected event(s)��6/   $y�Visible=�6o   m� 5      -   5        $��cm_view_event_properties��5      $��
Properties��6.   $y�Visible=�6f   5      ��5      �� 5       �� 
TargetType9   3vostok.editor.wpf_controls.logic_view.event_control"  6   .R�5      �  � ColumnDefinitions 5      �� 5      $��1* �6   �� 5      $��1* �6   .+�5      �� $��3, 31, 0, 0q�6   $��2��6$   $��Stretch=�68   $��Center=�6U   $��2��6r   $��2q�6|    J� SnapsToDevicePixels . ��5      �� 5   	    �� Triggers 5   
   �� 5       �� Binding 6   ��  �� Path$ is_selected�	 �� ElementName$	 parent_control��
 �� Value
 true6X   .a�5      ��  �� Property � �� �� Value
 �����61   5      .�5   
   ��  � ��
 �����6/   5   
   5!      F� 5"      $��m_event_border��6   $��2��6$   $��Center=�68   +���� 	=  	= р� 	= р����� 	= ���	$��2��6w   
�����F� . ��5#      �� 5$   	    5%   
   �� 5&       6   �� $ is_selected�$	 parent_control��
 true6X   .a�5'      ��  � ��
 �����6*   5(      .�5*   
   ��  � ��
 �����6(   5+   
   5-      �� 5.      $	��Top=�6   .+�5/      �� -   5        
 �� Top$ 6��5/       �� Left$ 20��6   $��
0, 0, 0, 6q�61   $��1��6E   $��12(�6�   $
��Left=�6�   
������ $��0q�6�    J� Opacity$ 1Q�6�   ��6U   �� *
event_name+ �� RelativeSource �� *TemplatedParent+.��6  ��50   	   �� 51   
    52      �� 53       6   �� $ IsMouseOver�$	 parent_control��
 true6Y   .a�54      ��  �@K�ZIndex$ 2��6,   55      .�57      ��  � ��
 �   �62   �� 58       �@K�ZIndex$ 0��6*   59      .��5:      5;   	   5<      5=      5>      5@      