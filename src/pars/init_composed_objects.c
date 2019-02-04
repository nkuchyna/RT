/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_composed_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:05:30 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 16:18:59 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_cylinder_closed(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 31 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].height = parse_height(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].cut_dir = ft_normalize(parse_cut_dir(s));
	sd->obj[i].cut_shift = parse_cut_shift(s);
	sd->obj[i].cut = parse_cut(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].obj_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void	parse_cone_closed(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 41 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].angle = parse_angle(s);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].height = parse_height(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].cut_dir = ft_normalize(parse_cut_dir(s));
	sd->obj[i].cut_shift = parse_cut_shift(s);
	sd->obj[i].cut = parse_cut(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].obj_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void	parse_tunel(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 11 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].s_radius = parse_s_radius(s);
	sd->obj[i].height = parse_height(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void	parse_bocal(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 12 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = parse_dir(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].height = parse_height(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void	parse_box(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 13 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].a = parse_a(s);
	sd->obj[i].b = parse_b(s);
	sd->obj[i].c = parse_c(s);
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}
