////////////////////////////////////////////////////////////////////////////
//	Created 	: 28.10.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_RENDER_ENGINE_PS3_WORLD_H_INCLUDED
#define VOSTOK_RENDER_ENGINE_PS3_WORLD_H_INCLUDED

#include <vostok/render/facade/common_types.h>
#include <vostok/render/facade/debug_renderer.h>
#include <vostok/render/engine/base_classes.h>
#include <vostok/render/core/memory.h>

namespace vostok {
	namespace ui {
		struct world;
		struct font;
	}
namespace particle {
	class particle_system_instance;
	typedef	resources::resource_ptr<
		resources::unmanaged_resource,
		resources::unmanaged_intrusive_base
	> particle_system_instance_ptr;

	class particle_system;
	typedef	resources::resource_ptr<
		resources::unmanaged_resource,
		resources::unmanaged_intrusive_base
	> particle_system_ptr;

	enum enum_particle_render_mode;
	struct preview_particle_emitter_info;
	struct world;
} // namespace particle

namespace render {

namespace debug {
	struct vertex;
} // namespace debug

namespace ui {
	struct vertex;
} // namespace ui

class render_output_window;

class render_model_instance;
typedef	resources::resource_ptr<
	render_model_instance,
	resources::unmanaged_intrusive_base
> render_model_instance_ptr;

class speedtree_instance;
typedef	resources::resource_ptr<
	speedtree_instance,
	resources::unmanaged_intrusive_base
> speedtree_instance_ptr;

enum scene_view_mode;
struct light_props;
struct decal_properties;

enum enum_render_stage_type;

typedef math::rectangle< math::float2 >					viewport_type;

namespace engine {

class world : private boost::noncopyable {
public:
	typedef vector< vertex_colored >				colored_vertices_type;
	typedef vector< u16 >							colored_indices_type;
	typedef ui::vertex const *						ui_vertices_type;

public:
					world							( );
					~world							( );
			void	initialize						( );

			void	set_renderer_configuration		( fs_new::virtual_path_string const&, bool ) { NOT_IMPLEMENTED(); }
			void	apply_render_options_changes	( ) { NOT_IMPLEMENTED(); }
			
			void	clear_resources					( );

			void 	draw_lines						( scene_ptr const& scene, debug_vertices_type const& vertices, debug_indices_type const& indices );
			void 	draw_triangles					( scene_ptr const& scene, debug_vertices_type const& vertices, debug_indices_type const& indices );

			particle::world* get_particle_world		( scene_ptr const& scene );

// world methods
public:
			void	set_view_matrix					( scene_view_ptr const& scene_view, math::float4x4 const& view_matrix );
			void	set_projection_matrix			( scene_view_ptr const& scene_view, math::float4x4 const& projection );
			void	set_world_matrix				( scene_view_ptr const& scene_view, math::float4x4 const& w );

	math::uint2		window_client_size				( render::render_output_window_ptr const& render_output_window );

			void	clear_zbuffer					( float z_value );

	static	void	draw_text						(
						vostok::vectora< ui::vertex >& output,
						pcstr const& text,
						vostok::ui::font const& font,
						vostok::float2 const& position,
						vostok::math::color const& text_color,
						vostok::math::color const& selection_color,
						u32 max_line_width,
						bool is_multiline,
						u32 start_selection,
						u32 end_selection
					);

			void	draw_scene						( scene_ptr const& scene, scene_view_ptr const& view, render_output_window_ptr const& output_window, viewport_type const& viewport, boost::function< void (bool) > const& on_draw_scene);
			void	end_frame						( );

			u32		frame_id						( );
			void	draw_ui_vertices				( ui_vertices_type vertices, u32 const & count, int prim_type, int point_type );

			void	reload_shaders					( );
			
			void	add_speedtree_instance			( scene_ptr const& in_scene, render::speedtree_instance_ptr const& v, float4x4 const& transform, bool populate_forest );
			void	remove_speedtree_instance		( scene_ptr const& in_scene, render::speedtree_instance_ptr const& v, bool populate_forest );
			void	update_speedtree_instance		( scene_ptr const& in_scene, render::speedtree_instance_ptr const& v, float4x4 const& transform, bool populate_forest );
			void	populate_speedtree_forest		( scene_ptr const& in_scene );
			void	reload_modified_textures		( );

			void	add_model						( scene_ptr const& in_scene, render_model_instance_ptr const& v, float4x4 const& transform, bool apply_transform = true );
			void	update_model					( scene_ptr const& in_scene, render_model_instance_ptr const& v, math::float4x4 const& transform );
			void	remove_model					( scene_ptr const& in_scene, render_model_instance_ptr const& v );
			void	set_model_material				( render::render_model_instance_ptr const& v, fs_new::virtual_path_string const& subsurface_name, resources::unmanaged_resource_ptr const& mtl_ptr);
			void	set_speedtree_instance_material ( render::speedtree_instance_ptr const& v, fs_new::virtual_path_string const& subsurface_name, resources::unmanaged_resource_ptr const& mtl_ptr);
			void	set_model_visible				( render::render_model_instance_ptr const& v, fs_new::virtual_path_string const& subsurface_name, bool value );
			void	update_model_vertex_buffer		( render_model_instance_ptr const& v, vectora<vostok::render::buffer_fragment> const& fragments );
			void	update_model_index_buffer		( render_model_instance_ptr const& v, vectora<vostok::render::buffer_fragment> const& fragments );

			void	add_light						( scene_ptr const& in_scene, u32 id, light_props const& props );
			void	update_light					( scene_ptr const& in_scene, u32 id, light_props const& props );
			void	remove_light					( scene_ptr const& in_scene, u32 id );
			
			void	add_decal						( scene_ptr const& scene, u32 id, render::decal_properties const& properties );
			void	update_decal					( scene_ptr const& scene, u32 id, render::decal_properties const& properties );
			void	remove_decal					( scene_ptr const& scene, u32 id );

			void	update_system_model				( render::render_model_instance_ptr const& v, vostok::math::float4x4 const& transform);

			void	set_model_ghost_mode			( render::render_model_instance_ptr const& v, bool value);

			void	draw_model_selections			( render::vector< render::render_model_instance_ptr > const& models);
			void	set_selection_parameters		( math::float4 const& selection_color, float selection_rate );
			void	update_skeleton					( render::render_model_instance_ptr const& v, math::float4x4* matrices, u32 count );

			void	terrain_add_cell				( scene_ptr const& in_scene, render::render_model_instance_ptr const& v);
			void	terrain_remove_cell				( scene_ptr const& in_scene, render::render_model_instance_ptr const& v);
			void 	terrain_update_cell_buffer		( scene_ptr const& in_scene, render::render_model_instance_ptr const& v, vostok::vectora<terrain_buffer_fragment> const& fragments, float4x4 const& transform);
			void 	terrain_update_cell_aabb		( scene_ptr const& in_scene, render::render_model_instance_ptr const& v, math::aabb const & aabb);
			void 	terrain_add_cell_texture		( scene_ptr const& in_scene, render::render_model_instance_ptr const& v, fs_new::virtual_path_string const & texture, u32 user_tex_id);
			void 	terrain_remove_cell_texture		( scene_ptr const& in_scene, render::render_model_instance_ptr const& v, u32 user_tex_id);
			void	terrain_exchange_texture		( scene_ptr const& in_scene, fs_new::virtual_path_string const & old_texture, fs_new::virtual_path_string const & new_texture);

			void	setup_view_and_output			( scene_view_ptr const& view, render_output_window_ptr const& output_window, viewport_type const& viewport);

			void	setup_grid_render_mode			( u32 grid_density );
			void	remove_grid_render_mode			( );

			void	setup_rotation_control_modes	( int mode );	

			void	play_particle_system			( scene_ptr const& in_scene, particle::particle_system_instance_ptr in_instance, bool use_transform, bool always_looping, math::float4x4 const& transform );
			void	stop_particle_system			( scene_ptr const& in_scene, particle::particle_system_instance_ptr in_instance );
			void	remove_particle_system_instance	( particle::particle_system_instance_ptr in_instance, scene_ptr const& in_scene );
			void	update_particle_system_instance	( particle::particle_system_instance_ptr instance, scene_ptr const& in_scene, vostok::math::float4x4 const& transform, bool visible = true, bool paused = false);

#ifndef MASTER_GOLD
			void	update_preview_particle_system	( particle::particle_system** preview_ps, scene_ptr const& in_scene, configs::lua_config_value config_value );
	void update_preview_particle_system_transform	( particle::particle_system** preview_ps, scene_ptr const& in_scene, math::float4x4 const& transform );
			void	add_preview_particle_system		( particle::particle_system** preview_ps, scene_ptr const& in_scene, configs::lua_config_value init_values, math::float4x4 const& transform = math::float4x4().identity() );
			void	remove_preview_particle_system	( particle::particle_system** preview_ps, scene_ptr const& in_scene );
			void	restart_preview_particle_system	( vostok::particle::particle_system** preview_ps, scene_ptr const& in_scene );
			void	set_looping_preview_particle_system	( particle::particle_system** preview_ps, scene_ptr const& scene, bool looping );
			void	show_preview_particle_system	( particle::particle_system** preview_ps, scene_ptr const& scene );
			void	draw_terrain_debug				( );
			void gather_preview_particle_system_statistics	( particle::particle_system** preview_ps, scene_ptr const& in_scene, particle::preview_particle_emitter_info* out_info );
			u32	get_num_preview_particle_system_emitters	( particle::particle_system** in_ps_out_ptr, scene_ptr const& in_scene ) const;
			void	select_particle_system_instance	( scene_ptr const& scene, particle::particle_system_instance_ptr const& instance, bool selected );
			void	select_speedtree_instance		( scene_ptr const& scene, render::speedtree_instance_ptr const& instance, bool is_selected );
			void	select_model					( scene_ptr const& scene, render_model_instance_ptr const& v, bool is_selected );
			void	enable_terrain_debug_mode		( bool is_enabled );
			void	draw_render_statistics			( vostok::ui::world* ui_world );
			void	draw_screen_lines				( scene_ptr const& scene, float2 const* points, u32 count, math::color const& color, float width, u32 pattern );
			void	draw_3D_screen_lines			( scene_ptr const& scene, float3 const* points, u32 count, math::color const& color, float width, u32 pattern, bool use_depth );
			void	draw_3D_screen_point			( scene_ptr const& scene, float3 const& position, math::color color, float width, bool use_depth );
			
			void	apply_material_changes			( fs_new::virtual_path_string const& material_name, vostok::configs::lua_config_value const& config_value );
#endif // #ifndef MASTER_GOLD

			void	set_slomo						( vostok::render::scene_ptr const& in_scene, float time_multiplier );
			void	toggle_render_stage				( enum_render_stage_type stage_type, bool toggle );
			void	set_view_mode					( scene_view_ptr const& view_ptr, scene_view_mode view_mode );
			void	set_particles_render_mode		( scene_view_ptr const& view_ptr, vostok::particle::enum_particle_render_mode render_mode );
			void	set_post_process				( scene_view_ptr const& view_ptr, resources::unmanaged_resource_ptr const& post_process_resource);
			void	enable_post_process				( scene_view_ptr const& view_ptr, bool enable );

	particle::world&	particle_world				( scene_ptr const& scene );

			void	set_sky_material				( scene_ptr const& scene, resources::unmanaged_resource_ptr mtl_ptr);

private:
	float4x4		m_view_matrix;
	float4x4		m_projection_matrix;
	viewport_type	m_viewport;
	u32				m_frame_id;
}; // class world

} // namespace engine
} // namespace render
} // namespace vostok

#endif // #ifndef VOSTOK_RENDER_ENGINE_PS3_WORLD_H_INCLUDED
