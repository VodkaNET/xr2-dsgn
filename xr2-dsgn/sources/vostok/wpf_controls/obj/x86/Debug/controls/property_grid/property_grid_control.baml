   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullU/clr-namespace:vostok.editor.wpf_controls.panels!vostok.editor.wpf_controls.panels  5      D    >vostok.editor.wpf_controls.property_grid.property_grid_control   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      @panels/clr-namespace:vostok.editor.wpf_controls.panels    5      -   5        $��	this_ctrl��5      $��23��5      $��50��5      .��5      �� -   5        #��Z�5   
   $��1q�6E   
�������._�5      5   /vostok.editor.wpf_controls.panels.scroll_viewer  $
��Auto=�6   $��0q�6<   .��5      ��   � IsSharedSizeScope  . .+�5      � -   5        $��m_columns_header��5       � ColumnDefinitions 5      �� 5      -   5         ��Name$% m_left_header_column_definition��5   E   $
��Auto �6    z� SharedSizeGroup$ PropertyName��6&   6E   �� 5      $��3 �6   �� 5      -   5        $&  m_right_header_column_definition��5   #   $��* �6   6#   5      �� 5      -   5        $��m_properties_panel��5      $��0q�6.    K� ZIndex$	 500��6B    �� 
GroupStyle 5      (  "System.Windows.Controls.GroupStyle  5         ContainerStyle 5   	   �� 5   
   .�5      ��  �� Property � �� �� Value 5      �� 5      .R�5      �� 	 � 	Resources	 5          bool_to_visibility_converter��%   &	        �� 5       6-   5!      .+�5"      ]� #��Z�6   .+�5$      �� $
��Left=�6   $��
2, 0, 0, 0q�6-   ._�5%      d� $��toggle_button��6   $��11��63   $��11��6>   $��
0, 0, 1, 0q�6J   
 d� 	IsChecked$

 trueY�6^    �� 	ClickMode$ Press=�5&      $
��Left=�6'   .��5'      �� $��5��6   $��5��6#   ._�5(      F�  F�Name$ 
ExpandPath��6   $��Center=�6,   $	��Top=�6I   
���   �$��1��6p   ��5)      �� 5*       �� 
TargetType" F�6   .�5+      ��  � ��+ ��    �%& �@KL �%& Р%&     Ѡ%& @KL 	6-    �� Triggers 5,      �� 5-       �� Binding 6#   �� *	IsChecked+ �� ElementName$ toggle_button�� �� Value True6\   .a�5.      ��  � �� ��    �%& �@KL �%& 	6/   5/      51      53      54      55      56      �� 58      $
��Bold"�60   #��Z�6B   $��Center=�6�    �� Padding$ 15, 0, 0, 2q�6�   ��6   �� *Name+6�   59      �� 5:      $��items_presenter��6   y�65   �� *	IsChecked+$ toggle_button�� �� 	Converter# [  5;      5<      5>      5?      5A   	   5C      5D      5E      5F      5G      