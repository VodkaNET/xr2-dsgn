   M S B A M L   `   `   `  ����G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nulla5clr-namespace:vostok.editor.wpf_controls.color_picker'vostok.editor.wpf_controls.color_picker  5      U/clr-namespace:vostok.editor.wpf_controls.panels!vostok.editor.wpf_controls.panels  5      8   2vostok.editor.wpf_controls.color_picker.hsv_circle   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      Lcolor_picker5clr-namespace:vostok.editor.wpf_controls.color_picker    5      @panels/clr-namespace:vostok.editor.wpf_controls.panels    5      -   5        $��this_control��5      $	��265��6   $	��265��6     � 	Resources  5      K  Evostok.editor.wpf_controls.color_picker.color_rgb_component_extracter   opacity_extractor��%   &	          5      6/   5	      .��5
      � .+�5      :  4vostok.editor.wpf_controls.color_picker.hue_spectrum  -   5          Name$ m_hue_spectrum��5      :  4vostok.editor.wpf_controls.color_picker.hue_spectrum   hue_changed$  m_hue_spectrum_hue_changed��6H    K� ZIndex$	 150��66   6H   :   4vostok.editor.wpf_controls.panels.single_place_panel  5      -   5          Name$&  m_saturation_brightness_spectrum��5      :   4vostok.editor.wpf_controls.panels.single_place_panel   PreviewMouseDown$&  saturation_brightness_mouse_down��5         PreviewMouseMove$&  saturation_brightness_mouse_move��5         PreviewMouseUp$$ saturation_brightness_mouse_up��5      $	 300��5   H   }�.  $	��180��5      $	��156��6   $��0, 51, 0, 0q�6%   .+�5      F� ��5      B� 5      .��5      E�  E� 
StartPoint$
 0, 0&�6   .��5   	   �� 	 �� Point$	 180, 0&�6   �� 5   	   $	 90, 156&�6   �� 5   	   $
	 0, 0&�6   5   	   5      ��5      L� 5      
 j� Viewport$
 0,0,0.15,0.15�6    j� TileMode$
 Tile=�6-    L� Drawing 5#      I� 5$   	   .��5%   
   �  � Brush
 ����� � Geometry 5&      �� 5'       �� Rect$ 0,0,180,156�6   5)      � 5+   
   
 �   � 5,      � 5-      .��5.      �� $ 	0,0,90,78�6   �� 5/      $ 90,78,90,78�6   50      52      53   
   55      57      F� 58      
���   �$��1��6   ��59      B� 5:      .��5;      E� $
 0, 0&�6   .��5<   	   �� $	 180, 0&�6   �� 5=   	   $	 90, 156&�6   �� 5>   	   $
	 0, 0&�6   5?   	   5@      ��5B      L� 5C       �� Opacity 6   �� *selected_color+ �� ElementName$ this_control�� �� 	Converter# [   �� ConverterParameter$ 3�� �� Mode$ OneWay=� 5D      I� 5E   	   .��5F   
   �  5G      �� 5H      $ 0, 0, 180, 156�6    5J      �� 5K      -   5        m_triangle_hue_color��5K      5M      �� 5N   
    �� ImageSource$ Saturation.png��6    �� Rect 5O      � 5P       � X$ 0Q�6    � Y$ 0Q�6    � Width$	 180Q�6    � Height$	 156Q�6)   5R      � 5S   
    5T      �� 5U      $ 0, 0, 180, 156�6    5W      �� 5X       �� 
StartPoint$ 0.5, 1&�6     �� EndPoint$ 0.50,0&�64   .��5Y      �  � Offset$	 0.0Q�6    � Color$ Black��6'   � 5Z      $	 1.0Q�6   $ 	#00000000��6'   5[      5]      5^   
   5`      5b      F� 5c      -   5        $$��m_saturation_brightness_marker��5c   
   $��2��60    � Cursor$ Cross��6D   
������ ��5d      @� 5e        @� RadiusX$  7Q�6   ! @� RadiusY$! 7Q�6#   ��5g      �� 5h      -   5        markerBrush��" �� Color$" Black��5h   ,   5j      5k      5l      5m      