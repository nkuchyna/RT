#ifndef FT_CL_H
# define FT_CL_H
# define WIDTH 512
# define HEIGHT 512
# define T_MAX 1e20
# define T_MIN 0.01
# define SAMPS 10000
# define NOISE 20
# define NON_COMPL(x) ((x) > -1e-9 && (x) < 1e-9)

typedef struct		s_obj
{
	float3			pos;
	float3			dir;
	float3			color;
	float3			emission;
	float3			c1;
	float3			c2;
	float3			c3;
	float3			cut_dir;
	float3			cut_shift;
	float3			obj_rotation;
	float3			text_rotation;
	float3			m_blur;
	float			diffuse;
	float			refraction;
	float			s_radius;
	float			radius;
	float			angle;
	float			c;
	float			height;
	float			a;
	float			b;
	float			m;
	float			len_ac;
	float			cos_pow;
	float			tscale;
	int				count;
	int				type_inter;
	int				cut;
	int				id;
	int				refl_type;
	int				texture;
	int				bump;
	int				pattern;
	int				negative;
}					t_obj;

typedef struct		s_light
{
	float3			pos;
	float3			dir;
	float3			color;
	float3			attenuation;
	float			phi;
	float			spotatt;
	int				n;
	int				id;
}					t_light;

typedef struct		s_cam 
{
	float3			pos;
	float3			dir;
	int				i;
}					t_cam;

typedef struct		s_render
{
	float3			ray[2];
	float3			cx;
	float3			cy;
	float3			color;
	float			dx;
	float			dy;
	float			rand;
	int				x;
	int				y;
	int				s;
}					t_render;

typedef struct		s_radiance
{
	t_obj			elena;
	float3			x;
	float3			n;
	float3			nl;
	float3			f;
	float3			res;
	float			t;
	float			type_inter;
	float			p;
	float			pdf;
	int				id;
	int				l_id;
	int				neg;

}					t_radiance;

void				intersection(__global t_obj *all, t_radiance *r, float3 o,
												float3 d, unsigned int seed);
unsigned int		ParallelRNG( unsigned int x );
unsigned int		ParallelRNG3( unsigned int x, unsigned int y,
															unsigned int z );
int					count_scene(int o);
int					check(int x, int cam, int cou);
int					count_of_pos(int res);
float				rand_ri (unsigned int *seed);
float3				lighting(__global t_obj *obj, __constant t_light *light,
													t_radiance r, float3 dir);
float3				radiance(__global t_obj *obj, __constant t_light *light,
							float ambient, float3 o, float3 dir, int depth,
							unsigned int seed, float3 m_dir, int neg,
							__read_only image2d_t image,
							__read_only image2d_t image1,
							__read_only image2d_t image2,
							__read_only image2d_t image3, int *permutation);
float3				direct(__constant t_light *l, __global t_obj *all,
													t_radiance r, float3 dir);
float3				mirror_refl(float3 n, float3 dir);
float3				hemisphere_ray(t_radiance *r, float3 w, unsigned int seed,
																float alpha);	
/*
** HELPER
*/
float				ft_define_min(float t1, float t2);
float				ft_calc_shift_radius(t_obj *obj);
float				ft_half_sphere_closed_inter(float3 ov, float3 point,
									t_obj *obj, int neg, __global t_obj *all);
float				ft_sphere_inter_ob(float3 ov, float3 point, t_obj *obj);
float				ft_solve_quadratic_eq(float k1, float k2, float k3);
float				ft_define_tmin_m(float3 t, float *m, t_obj *obj);
float				ft_check_pnt(float3 k, float3 ov, float3 point, t_obj *obj,
										int neg, __global t_obj *all);
float				ft_check_cut(float t_min, t_obj *obj, float3 p);
float				ft_calc_len_to_plane(float3 pl_pos, float3 p, float3 c_dir);
float				ft_define_torus_t_min(float *s, int num);
float				ft_define_bocal_inter(float *t, t_obj *obj,
															float *type_inter);
int					ft_calc_coef_and_solve_quadr_eq(float *s, float u,
															float v, float q);
int					ft_transform_into_two_quadr_eq(float *s, float p,
															float r, float q);
int					ft_find_quart_solution(float *s, float p, float q, float r);
int					ft_solve_quart_eq(float *c, float *s);
int					ft_solve_quadratic_eq_adv(float *c, float *s);
int					ft_find_cubic_solution_sub(float *s, float q);
int					ft_find_cubic_solution(float *s, float p, float q);
int					ft_solve_cubic_eq(float *c, float *s);
int					ft_cut_plane(float t, __global t_obj *obj, float3 point,
																float3 ov);
void				ft_solve_quadratic_eq_base(float3 k, float3 *t);
void				half_sphere_closed_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				ft_define_eq_params(float *c, float3 oc, float3 ov,
														__global t_obj *obj);
void				half_sphere_closed_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				half_sphere_closed_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				cone_closed_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				top_bocal_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				ft_top_bocal_inter(float *t, float3 ov,
													float3 point, t_obj *obj);
/*
** TEXTURES
*/
float3				ft_calc_texture_coord(float u, float v,
									__read_only image2d_t image, float tscale);
float3				ft_define_color_from_texture(float3 xy,
												__read_only image2d_t image);
float3				ft_add_pattern(t_radiance r, __global t_obj *all,
															float u, float v);
float3				ft_def_sph_pat(int pattern, float u, float v,
															float3 obj_color);
float3				ft_def_cone_pat(int pattern, float u, float v,
															float3 obj_color);
float3				ft_def_cyl_pat(int pattern, float u, float v,
													float3 obj_color, float k);
float3				ft_def_plane_pat(int pattern, float u, float v,
															float3 obj_color);
float3				ft_mix(float3 color1, float3 color2, float a);
float3				ft_get_shift_normal(float3 xy, __read_only image2d_t image);
float3				ft_bump_map(float3 p, __read_only image2d_t image,
																t_radiance r);
float3				ft_covret_rgba_to_rgb(float4 rgba, float3 obj_color);
float				ft_define_height_coordinate(t_radiance r,
											__global t_obj *all, float height);
float				ft_define_waved_normal(float u, float v, int id);
void				ft_calc_uv_plane_coord(t_radiance r, float *u, float *v);
void				ft_calc_uv_cylndr(__global t_obj *all, t_radiance r,
														float *u, float *v);
void				ft_calc_uv(t_radiance r, __global t_obj *all, float *u,
																float *v);
/*
** INTERFUNCIONS
*/
float				map(float3 p);
float				length8(float2 v);
float				map_tor(float3 p, float2 t);
float				map_box(float3 p, float b);
float				inv_sqrt( float number );
float				ft_plane_inter(float3 ov, float3 point, t_obj *obj);
float				ft_plane_inters(float3 ov, float3 point,
													__global t_obj *obj);
float				ft_sphere_inter(float3 ov, float3 point, t_obj *obj,
											int neg, __global t_obj *all);
float				ft_sphere_inters(float3 ov, float3 point,
													__global t_obj *obj);
float				ft_cylinder_inter(float3 ov, float3 point, t_obj *obj,
											int neg, __global t_obj *all);
float				ft_cone_inter(float3 ov, float3 point, t_obj *obj,
											int neg, __global t_obj *all);
float				ft_ellips_inter(float3 ov, float3 point, t_obj *obj);
float				ft_paraboloid_inter(float3 ov, float3 point,
								t_obj *obj, int neg, __global t_obj *all);
float				ft_torus_inter(float3 ov, float3 point,
													__global t_obj *obj);
float				torus88_inter(float3 ov, float3 point,
													__global t_obj *obj);
float				perfcube_inter(float3 ov, float3 point,
													__global t_obj *obj);
float				heart_inter(float3 ov, float3 point,
													__global t_obj *obj);
float				mandelbulb_inter(float3 ov, float3 point, t_obj *obj);
float				ft_triangle_inter(float3 ov, float3 point, t_obj *obj);
float				ft_triangle_inters(float3 ov, float3 point,
													__global t_obj *obj);
float				ft_tetragon_inter(float3 ov, float3 point, t_obj *obj);
float				ft_disk_inter(float3 ov, float3 point, t_obj *obj);
float				ft_tunel_inter(float3 ov, float3 point, t_obj *obj,
							int neg, __global t_obj *all, float *type_inter);
float				ft_bocal_inter(float3 ov, float3 point, t_obj *obj,
							int neg, __global t_obj *all, float *type_inter);
float				ft_cylinder_closed_inter(float3 ov, float3 point,
						t_obj *obj, int neg,
						__global t_obj *all, float *type_inter);
float				ft_cone_closed_inter(float3 ov, float3 point,
						t_obj *obj, int neg,
						__global t_obj *all, float *type_inter);
float				ft_box_inter(float3 ov, float3 point, t_obj *obj);
int					ft_check_neg_cone_cyl(__global t_obj *neg_obj, float3 pc);
int					ft_check_neg_obj(__global t_obj *obj, float3 ov,
													float3 point, float t);
/*
** NORMALS
*/
void				plane_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				sphere_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				cylinder_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				cone_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				torus_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				ellips_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				paraboloid_normal(t_radiance *r, t_obj obj,
														float3 o, float3 d);
void				tunel_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				bocal_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				cylinder_closed_normal(t_radiance *r, t_obj obj,
															float3 o, float3 d);
void				cylinder_closed_normal(t_radiance *r, t_obj obj,
															float3 o, float3 d);
void				box_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
void				mandelbulb_norm(t_radiance *r, t_obj obj,
															float3 o, float3 d);
void				torus88_normal(t_radiance *r, t_obj obj,
															float3 o, float3 d);
void				perfcube_normal(t_radiance *r, t_obj obj,
															float3 o, float3 d);
void				heart_normal(t_radiance *r, t_obj obj, float3 o, float3 d);
/*
** VECTOR FUNCTIONS
*/
float3				ft_vector_sub(float3 vec1, float3 vec2);
float3				ft_vector_add(float3 vec1, float3 vec2);
float3				ft_normalize(float3 vec);
float3				ft_cross(float3 vec1, float3 vec2);
float3				ft_rotate_vector(float3 obj_rotation, float3 dir);
float3				ft_vector_mult(float3 vec, float num);
float				ft_vector_dot(float3 vec1, float3 vec2);
float				ft_vector_len(float3 vec);
void				ft_calc_uv(t_radiance r, __global t_obj *obj,
														float *u, float *v);
void				ft_calc_uv_cylndr(__global t_obj *obj, t_radiance r,
														float *u, float *v);
void				ft_calc_uv_plane_coord(t_radiance r, float *u, float *v);
/*
** PERLIN
*/
float				ft_general_perlin(float3 point, int octaves,
									float persistence, int *permutation);
float				perlin(float x, float y, float z, int *p);
float				grad(int hash, float x, float y, float z);
float				lerp(float a, float b, float x);

#endif
