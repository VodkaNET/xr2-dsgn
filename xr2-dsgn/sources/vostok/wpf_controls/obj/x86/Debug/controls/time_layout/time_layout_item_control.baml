   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullG(clr-namespace:vostok.editor.wpf_controlsvostok.editor.wpf_controls  5      9    3vostok.editor.wpf_controls.time_layout_item_control   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      8local(clr-namespace:vostok.editor.wpf_controls    5      -   5        $��Stretch=�5      .��5	      �� $��32��6   $��Stretch=�6   .+�5
   
   �� -   5        $��ControlBorder��5
      $��30��6   
  �� Top$  1��62   
����  �$��1q�6X   $��1��6l   |�. ._�5      ]� -   5        ��.  � Cursor$ 	ScrollAll��5   *   ��5      �� 5       �� Triggers 5      �� 5   	    �� Binding 6   �� *is_selected+ �� Value True65   .a�5   
   ��  �� Property � �� �� Value
 �k���6/   5   
   �� 5   	    6   �� *is_selected+	 False65   .a�5   
   ��  � ��
 ���F�6/   5   
   5      .+�5      >� -   5        $��LeftEdge��5      $
��Left=�6"   $
��Auto��68   $��5��6F   
������ ��5      �� 5       5   	   �� 5    
    6   �� *is_in_multiselection+ true6?   .a�5!      ��  �@�Cursor$ 	ScrollAll��6,   5"      �� 5#   
    6   �� *is_in_multiselection+	 false6?   .a�5$      ��  �@�Cursor$ SizeWE��6,   5%      5'   	   5)      >� 5*      -   5        $��	RightEdge��5*      $��Right=�6#   $
��Auto��6:   $��5��6H   
������ ��5+      �� 5,       5-   	   �� 5.   
    6   �� *is_in_multiselection+ true6?   .a�5/      ��  �@�Cursor$ 	ScrollAll��6,   50      �� 51   
    6   �� *is_in_multiselection+	 false6?   .a�52      ��  �@�Cursor$ SizeWE��6,   53      55   	   57      �� 58      -   5         ��Name$ start_time_text��58      |�.  $��0q�6F   
������ $
��Left=�59   3   $��Center=�6I    �� TextAlignment$
 Left=�5:      .��5;   2   5<      �� 5=      -   5        $ end_time_text��5=      |�.  $��0q�6@   
������ $��Right=�5>   3   $��Center=�6J   $ Right=�5?      .��5@   O   5A      �� 5B      -   5        $ length_time_text��5B      $��0q�64   |�.  
������ $	��Top=�5C   3   $��Center=�6H   $ Center=�6e   .��5D   N   5E      �� 5F      $��Bottom=�6   $��Bottom=�61   	 �� TextAlignment$	 Center=�6L   ��5G      �� *	item_text+5H      5I      5J      5L      