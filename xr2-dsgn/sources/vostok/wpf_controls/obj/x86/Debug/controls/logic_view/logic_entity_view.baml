   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]3clr-namespace:vostok.editor.wpf_controls.hypergraph%vostok.editor.wpf_controls.hypergraph  5   <   =    7vostok.editor.wpf_controls.logic_view.logic_entity_view   5   	   \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      H
hypergraph3clr-namespace:vostok.editor.wpf_controls.hypergraph    6<   -   5          ��Name$  parent_control��5   	   $��4q�5      |�. $	��150��5      
������ ��5	      �� 5
       �� Triggers 5      �� 5       �� Binding 6   ��  �� Path$ IsMouseOver� �� ElementName$ parent_control�� �� Value true6S   .a�5      ��  �� Property � �� �� Value
 ��ح�6,   5      �� 5       6   �� $ is_selected�$ parent_control�� true6S   .a�5      ��  � ��
 �����6,   5      .�5      ��  � ��
 �����6*   5      ._�5      ]� .+�5      n� -   5         n�Name$ bottom_grip��5   
   $��Bottom=�6;   	 � Cursor$	 SizeNS��6S   ��5      �� 5      .R�5      �� $��10��6   
����ح�
�������$��3q�6D   5      5      5      ]� 5      $
��Left=�6   .+�5       �� -   5        $��logic_entity_resource_top��5    !   $	��Top=�6   $��20��6C   $	��150��6O   $��2 2 2 0q�6\   
�������|�. 
�����F�._�5!      �� -   5        
 ��Name$
 	item_text��5!      $��ItemName��6$    �� TextAlignment$ Center=�64   6K   5"      �� 5#      $	��Top=�6   $	��150��6!   $��26��6-   
�����F�$��2q�6R   
�����F�._�5$      �� -   5        $��Stretch=�5$       J� SnapsToDevicePixels . .��5%      �� $��Add Behaviour��6   $ Center=�6&   $��Center=�6=   $
��Wrap=�6X   5&      5'      �� 5(      $��Bottom=�6   $��30��6$   $	��150��60   $��2 0 2 2q�6<   
�������|�. 
�����F�._�5)      ]� .+�5*      �� $��20��6   $
��Left=�6   $��StartEvent: ��64   $��Center=�6H   $ Center=�6c   �� 5+      -   5         ��Name$ start_event_combobox��5+   ,   $��Center=�6   6�   5,      5-      �� 5.      $��Bottom=�6   $	��150��6$   
�����F�$��2q�6I   
�����F�._�5/      �� -   5         ��Name$" logic_entity_resource_button��5/   U   $��Stretch=�6   $��Stretch=�60    . .��50      �� -   5        $)  #logic_entity_resource_button_border��50      $��3q�6;   
�������
�����F�._�51      �� -	   5        $
 selected_resource��51      $��Selected Resource: none��6.   $ Center=�6M   $��Center=�6d   $
��Wrap=�6�   52      53      54      55      >   8vostok.editor.wpf_controls.hypergraph.hypergraph_control  57      -
   5          Name$ logic_hypergraph��57   �      	top_limit$ 0Q�6"      
left_limit$ 0Q�60      need_expand_to_field .    viewport_origin$	 0,0-�6[      is_zoomable .     
is_panable .     is_nodes_moveable .    is_fix_min_field_size .     field_bounds_inflate$	 0,0��6�      is_grid_enabled .  $��10(�66  58      59      5:      