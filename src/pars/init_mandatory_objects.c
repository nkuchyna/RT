/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mandatory_objects.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 13:54:28 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 16:20:29 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	initialize_obj(char *s, int i, t_sdl *sd)
{
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].color = parse_color(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].cut_dir = ft_normalize(parse_cut_dir(s));
	sd->obj[i].cut_shift = parse_cut_shift(s);
	sd->obj[i].cut = parse_cut(s);
	sd->obj[i].obj_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].texture = ft_define_text(sd->textures,
	s, "<texture>", "</texture>");
	sd->obj[i].bump = ft_define_text(sd->bump, s, "<bump>", "</bump>");
	sd->obj[i].tscale = parse_text_scale(s);
	sd->obj[i].pattern = parse_pattern(s);
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void		parse_cylinder(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 3 : 0;
	initialize_obj(s, i, sd);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].height = parse_height(s);
	if ((sd->obj[i].negative = parse_negative(s)) > 0)
		sd->neg = 1;
	ft_precalc_params(&sd->obj[i]);
}

void		parse_cone(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 4 : 0;
	initialize_obj(s, i, sd);
	sd->obj[i].angle = parse_angle(s);
	sd->obj[i].height = parse_height(s);
	if ((sd->obj[i].negative = parse_negative(s)) > 0)
		sd->neg = 1;
	sd->obj[i].bump = ft_define_text(sd->bump, s, "<bump>", "</bump>");
	sd->obj[i].tscale = parse_text_scale(s);
	sd->obj[i].pattern = parse_pattern(s);
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
	ft_precalc_params(&sd->obj[i]);
}

void		parse_sphere(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 2 : 0;
	initialize_obj(s, i, sd);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].obj_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].texture = ft_define_text(sd->textures,
	s, "<texture>", "</texture>");
	sd->obj[i].bump = ft_define_text(sd->bump, s, "<bump>", "</bump>");
	sd->obj[i].tscale = parse_text_scale(s);
	sd->obj[i].pattern = parse_pattern(s);
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
	sd->obj[i].height = 0;
	if ((sd->obj[i].negative = parse_negative(s)) > 0)
		sd->neg = 1;
	ft_precalc_params(&sd->obj[i]);
}

void		parse_plane(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 1 : 0;
	initialize_obj(s, i, sd);
	sd->obj[i].obj_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].texture = ft_define_text(sd->textures,
	s, "<texture>", "</texture>");
	sd->obj[i].bump = ft_define_text(sd->bump, s, "<bump>", "</bump>");
	sd->obj[i].tscale = parse_text_scale(s) * 0.01;
	sd->obj[i].pattern = parse_pattern(s);
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
	ft_precalc_params(&sd->obj[i]);
	if (ft_vector_compare(sd->obj[i].dir, sd->obj[i].cut_dir))
		sd->obj[i].id = -10;
}
