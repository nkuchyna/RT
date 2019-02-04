/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:38:48 by sperkhun          #+#    #+#             */
/*   Updated: 2018/08/27 12:38:50 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RT_H
# define FT_RT_H
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <OpenCL/opencl.h>
# include "deffs.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include "../libft/Libft/libft.h"
# include <errno.h>
# include <time.h>
# define WIDTH 512
# define HEIGHT 512
# define T_MAX 1e20
# define T_MIN 0.01
# define SAMPS 10000
# define MENU_RECT_NBR 36
# define MENU_HEIGHT 92
# define PARAM_NBR 15
# define MAX_TEXTURE_NBR 4
# define NON_COMPL(x) ((x) > -1e-9 && (x) < 1e-9)

typedef float			t_vector __attribute__((vector_size(sizeof(float)*3)));
typedef struct			s_cam
{
	cl_float3			pos;
	cl_float3			dir;
	int					i;
}						t_cam;

typedef struct			s_o
{
	cl_float3			*v;
	cl_float3			*vn;
	cl_float3			*vt;
	float				max;
	float				min;
	int					**f;
	int					c[4];
	int					fl;
	char				**sharp;
}						t_o;

typedef struct			s_obj
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			color;
	cl_float3			emission;
	cl_float3			c1;
	cl_float3			c2;
	cl_float3			c3;
	cl_float3			cut_dir;
	cl_float3			cut_shift;
	cl_float3			obj_rotation;
	cl_float3			text_rotation;
	cl_float3			m_blur;
	cl_float			diffuse;
	cl_float			refraction;
	cl_float			s_radius;
	cl_float			radius;
	cl_float			angle;
	cl_float			c;
	cl_float			height;
	cl_float			a;
	cl_float			b;
	cl_float			m;
	cl_float			len_ac;
	cl_float			cos_pow;
	cl_float			tscale;
	cl_int				count;
	cl_int				type_inter;
	cl_int				cut;
	cl_int				id;
	cl_int				refl_type;
	cl_int				texture;
	cl_int				bump;
	cl_int				pattern;
	cl_int				negative;
}						t_obj;

typedef struct			s_light
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			color;
	cl_float3			attenuation;
	float				phi;
	float				spotatt;
	int					n;
	int					id;
}						t_light;

typedef struct			s_sdl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	SDL_Surface			*screen;
	SDL_Surface			*texture1;
	SDL_Surface			*texture2;
	SDL_Surface			*texture3;
	SDL_Surface			*texture4;
	SDL_Rect			*menu;
	SDL_Rect			*places;
	SDL_Rect			menu_cover;
	SDL_Surface			**texts;
	SDL_Surface			*s;
	SDL_Window			*window;
	SDL_Event			event;
	TTF_Font			*font;
	SDL_Color			t_color;
	cl_float3			*color;
	t_cam				cam;
	t_light				*light;
	t_obj				*obj;
	t_obj				*obj_obj;
	cl_mem				objc;
	cl_mem				lightc;
	cl_mem				screenc;
	cl_mem				texturec1;
	cl_mem				texturec2;
	cl_mem				texturec3;
	cl_mem				texturec4;
	cl_int				err;
	size_t				global;
	size_t				local;
	size_t				globalsize;
	size_t				localsize;
	float				ambient;
	int					count;
	int					effect;
	int					id_sel_rect;
	int					id_sel_obj;
	int					id_sel_par;
	int					neg;
	int					gpu;
	int					is_running;
	unsigned int		number;
	char				**textures;
	char				**bump;
	char				*source_str;
}						t_sdl;

typedef struct			s_loop
{
	const Uint8			*keyboardstate;
	SDL_Surface			*sshot;
	cl_float3			angle;
	cl_float3			dir_old;
	cl_float3			dir;
	int					i;
	int					n;
	int					tmp;
	int					x;
	int					y;
	int					b;
	int					select_flag;
	int					ss;
	char				*text_str;
}						t_loop;

typedef struct			s_render
{
	cl_float3			ray;
	cl_float3			cx;
	cl_float3			cy;
}						t_render;
int						free_it(char *one, char *two, char *three);
void					init_int_array(int *arr, int count, int stuff);
void					upload_textures_and_bump(t_sdl *sd);
/*
** LOOP
*/
cl_float3				mousemot(cl_float3 dir);
float					ft_define_min(float t1, float t2);
float					ft_check_cut(float t_min, t_obj *obj, cl_float3 p);
float					ft_define_torus_t_min(float *s, int num);
float					ft_solve_quadratic_eq(float k1, float k2, float k3);
float					ft_define_tmin_m(cl_float3 t, float *m, t_obj *obj);
float					ft_check_pnt(cl_float3 k, cl_float3 ov,
												cl_float3 point, t_obj *obj);
int						ft_cut_plane(float t, t_obj *obj,
									cl_float3 point, cl_float3 ov);
void					ft_free_text_surf(SDL_Surface **texts);
void					sdl_mouse_button_down(t_sdl *sd, t_loop *l);
void					sdl_mouse_motion(t_sdl *sd, t_loop *l);
void					sdl_scan_code_up(t_sdl *sd, t_loop *l);
void					sdl_scan_code_down(t_sdl *sd, t_loop *l);
void					sdl_scan_code_s(t_sdl *sd, t_loop *l);
void					free_everything_left(t_sdl *sd);
void					free_everything_left2(t_sdl *sd);
void					loop(t_sdl *sd);
void					render(t_sdl *sd, int pt);
void					ft_putpixel(t_sdl *sd, cl_float3 color, int i, int pt);
void					init_sdl(t_sdl *sd);
void					clear_buf(cl_float3 *color);
void					ft_solve_quadratic_eq_base(cl_float3 k, cl_float3 *t);
void					ft_define_cut_dir(t_obj *obj);
void					ft_precalc_params(t_obj *obj);
void					ft_define_eq_params(float *c, cl_float3 oc,
											cl_float3 ov, t_obj *obj);
char					*ft_change_text_str(int i);
/*
** OPENCL
*/
void					error(cl_int e, t_sdl *sd);
void					init_cl(t_sdl *sd);
void					init_buffs(t_sdl *sd, int n, int s);
void					cl_enqueue_image(t_sdl *sd);
/*
** PARSING
*/
t_o						get_obj_data(char *s, int *i);
t_obj					*get_sphere(int count, t_o *o);
cl_float3				get_vector(char *index, char *x, char *y, char *z);
cl_float3				parse_color(char *obj);
cl_float3				parse_color_light(char *obj);
cl_float3				parse_dir(char *obj);
cl_float3				parse_m_blur(char *obj);
cl_float3				parse_emission(char *obj);
cl_float3				parse_pos(char *obj);
cl_float3				parse_c1(char *obj);
cl_float3				parse_c2(char *obj);
cl_float3				parse_c3(char *obj);
cl_float3				parse_cut_shift(char *obj);
cl_float3				parse_cut_dir(char *obj);
cl_float3				parse_pos_light(char *obj);
cl_float3				parse_dir_light(char *obj);
cl_float3				chk_vector(cl_float3 in);
cl_float3				ft_vector_mult(cl_float3 vec, float num);
cl_float3				ft_vector_div(cl_float3 vec, float num);
cl_float3				ft_vector_sub(cl_float3 vec1, cl_float3 vec2);
cl_float3				ft_vector_add(cl_float3 vec1, cl_float3 vec2);
cl_float3				ft_normalize(cl_float3 vec);
cl_float3				ft_cross(cl_float3 vec1, cl_float3 vec2);
float					parse_ambient(char *obj);
float					ft_vector_dot(cl_float3 vec1, cl_float3 vec2);
float					ft_vector_len(cl_float3 vec);
float					parse_diffuse(char *obj);
float					parse_cos_pow(char *obj);
float					parse_s_radius(char *obj);
float					parse_radius(char *obj);
float					parse_text_scale(char *obj);
float					parse_refract(char *obj);
float					parse_specular(char *obj);
float					parse_angle(char *obj);
float					parse_height(char *obj);
float					parse_c(char *obj);
float					parse_b(char *obj);
float					parse_a(char *obj);
float					parse_phi(char *obj);
float					parse_phi_light(char *obj);
float					parse_pattern(char *obj);
float					parse_negative(char *obj);
int						parse_scene_objects(t_sdl *sd, char *scene,
												int count, int i);
int						parse_scene_lights(t_sdl *sd, char *scene, int count);
int						check_in(char **s);
int						chk_tg(char *save, int *count, char *intag, int ret);
int						parse_cut(char *obj);
int						parse_material(char *obj);
int						ft_vector_compare(cl_float3 a, cl_float3 b);
int						read_scene_from_file(int fd, t_sdl *sd);
void					init_typical_obj(int i, t_sdl *sd);
void					parse_cone(char *s, int i, t_sdl *sd);
void					parse_cylinder(char *s, int i, t_sdl *sd);
void					parse_cylinder_closed(char *s, int i, t_sdl *sd);
void					parse_cone_closed(char *s, int i, t_sdl *sd);
void					parse_sphere(char *s, int i, t_sdl *sd);
void					parse_plane(char *s, int i, t_sdl *sd);
void					parse_torus(char *s, int i, t_sdl *sd);
void					parse_paraboloid(char *s, int i, t_sdl *sd);
void					parse_ellipsoid(char *s, int i, t_sdl *sd);
void					parse_triangle(char *s, int i, t_sdl *sd);
void					parse_tetragon(char *s, int i, t_sdl *sd);
void					parse_disk(char *s, int i, t_sdl *sd);
void					parse_tunel(char *s, int i, t_sdl *sd);
void					parse_bocal(char *s, int i, t_sdl *sd);
void					parse_box(char *s, int i, t_sdl *sd);
void					parse_obj_file(char *s, int i, t_sdl *sd);
void					parse_mandelbulb(char *s, int i, t_sdl *sd);
void					parse_torus88(char *s, int i, t_sdl *sd);
void					parse_perfcube(char *s, int i, t_sdl *sd);
void					parse_heart(char *s, int i, t_sdl *sd);
void					object_alloc(char *scene, t_sdl *sd, int *count);
void					ft_arrange_tetragon(t_obj *obj);
void					init_tetragon(t_obj *obj, cl_float3 *vec,
										char *s, cl_float3 *vec_2);
void					read_obj_file(int fd, t_sdl *sd, char *s);
void					init_triangle(t_obj *obj, cl_float3 *vec, char *s);
/*
** FOR MENU
*/
cl_float3				ft_rotate_vector(cl_float3 obj_rotation, cl_float3 dir);
cl_float3				ft_add_color_effect(int effect, cl_float3 color);
float					ft_sphere_inter(cl_float3 ov, cl_float3 point,
															t_obj *obj);
float					ft_sphere_inter_ob(cl_float3 ov, cl_float3 point,
															t_obj *obj);
float					ft_cone_inter(cl_float3 dir, cl_float3 point,
															t_obj *obj);
float					ft_cylinder_inter(cl_float3 ov, cl_float3 point,
															t_obj *obj);
float					ft_plane_inter(cl_float3 ov, cl_float3 point,
															t_obj *obj);
float					ft_ellips_inter(cl_float3 ov, cl_float3 point,
															t_obj *obj);
float					ft_disk_inter(cl_float3 ov, cl_float3 point,
															t_obj *obj);
float					ft_triangle_inter(cl_float3 ov, cl_float3 point,
													t_obj *obj);
float					ft_box_inter(cl_float3 ov, cl_float3 point, t_obj *obj);
float					ft_paraboloid_inter(cl_float3 ov,
									cl_float3 point, t_obj *obj);
float					ft_torus_inter(cl_float3 ov, cl_float3 point,
													t_obj *obj);
float					ft_bocal_inter(cl_float3 ov, cl_float3 point,
													t_obj *obj);
float					ft_cylinder_closed_inter(cl_float3 ov,
									cl_float3 point, t_obj *obj);
float					ft_cone_closed_inter(cl_float3 ov, cl_float3 point,
													t_obj *obj);
float					ft_tetragon_inter(cl_float3 ov, cl_float3 point,
													t_obj *obj);
float					ft_tunel_inter(cl_float3 ov, cl_float3 point,
													t_obj *obj);
int						ft_solve_quart_eq(float *c, float *s);
int						ft_solve_quadratic_eq_adv(float *c, float *s);
int						ft_solve_cubic_eq(float *c, float *s);
int						ft_define_text(char **textures, char *obj,
										char *t_beg, char *t_end);
int						ft_define_select_rect(int x, int y, SDL_Rect *menu);
int						ft_def_change_par_buttom(int id, int id_sel_par);
int						ft_define_sel_param(int button, int param);
int						ft_choose_obj(t_sdl *sd, int x, int y);
void					ft_add_texts(t_sdl *sd);
void					ft_change_obj_texture(int id_param, t_obj *obj);
void					ft_change_obj_params(t_obj *obj, int id, int id_param);
void					ft_change_obj_mater(int k, int id, int id_param,
															t_obj *obj);
void					cartoon(t_sdl *sd);
void					ft_init_edit_line(t_sdl *sd, int *i);
void					ft_init_main_line(t_sdl *sd, int *i);
void					ft_init_effect_line(t_sdl *sd, int *i);
void					ft_init_scale_ef_line(t_sdl *sd, int *i);
void					ft_init_system_line(t_sdl *sd, int *i);
void					ft_init_line_rect(int i, SDL_Rect *menu,
												int *x, int *y);
void					ft_init_places_rect(int i, SDL_Rect *places,
													int x, int y);
void					ft_add_menu(t_sdl *sd);
void					ft_create_menu(t_sdl *sd);
void					init_ttf(t_sdl *sd);
void					ft_menu_button_action(t_sdl *sd, int select_flag);

#endif
