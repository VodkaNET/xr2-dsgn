   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null]3clr-namespace:vostok.editor.wpf_controls.hypergraph%vostok.editor.wpf_controls.hypergraph  5      U/clr-namespace:vostok.editor.wpf_controls.panels!vostok.editor.wpf_controls.panels  5      >    8vostok.editor.wpf_controls.hypergraph.hypergraph_control   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      H
hypergraph3clr-namespace:vostok.editor.wpf_controls.hypergraph    5      @panels/clr-namespace:vostok.editor.wpf_controls.panels    5      -   5        |�. }�.   � ContextMenu  5      �� 5      -   5        $��m_context_menu��5   -   .@�5      m� -   5        $��cm_enable_disable_link��5      $��Disable Link��6,   $y�	Collapsed=�6d   m� 5      -   5        $��	cm_remove��5      $��Remove��6   $y�	Collapsed=�6Q   5      .��5      @   :vostok.editor.wpf_controls.panels.centralized_scroll_panel  -   5          Name$ m_field_scroller��5   #   @   :vostok.editor.wpf_controls.panels.centralized_scroll_panel   SizeChanged$! field_scroller_size_changed��5      .+�5      1   +vostok.editor.wpf_controls.hypergraph.field  -   5          Name$ m_field��5      }�.  .+�5      F� -   5        $��m_new_link_path��5   
   
���   �$��1��60    �� StrokeDashArray$
 8, 4R�6D    K� ZIndex$ 9000000��6[    J� IsHitTestVisible .  ��5      �� 5      -   5        m_new_link_line�� �� 
StartPoint$
 0, 0&�5   -    �� EndPoint$ 100, 100&�6?   5      �� 5      -	   5        $��m_link_icon_container��5      $ 9000001��6/   .@�5      F� -
   5        $��m_link_cancel_icon��5       .  
���  ��$��4��5       	 �� StrokeEndLineCap$	 Round=�6)   
 �� StrokeStartLineCap$
 Round=�6B   ��5!      B� 5"      .��5#   	   E�  E� 
StartPoint$ -10, -10&�6   .��5$   
   ��  �� Point$ 10, 10&�6   5%   
   E� 5&   	   $ -10, 10&�6   .��5'   
   �� $ 10, -10&�6   5(   
   5)   	   5+      F� 5,      -   5        $��m_link_apply_icon��5,       .  
��� �|�$��4��5-      $	 Round=�6/   $
 Round=�6H   ��5.      B� 5/      .��50   	   E� $ -10, -10&�6   .��51   
   �� $
 0, 0&�6   �� 52   
   $ 10, -20&�6   53   
   54   	   56      57      F� 58      -   5        $��m_selection_path��58   
   
���   �$��1��61   $
 3, 2R�6E   $ 9000000��6\    J� SnapsToDevicePixels . ��59      �� 5:      -   5        m_selection_rect�� �� Rect$ 20, 20, 50, 50�5:   3   5<      5=      5>      5?      