/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other_simple_objects.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:02:10 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 16:21:42 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_torus(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 5 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].s_radius = parse_s_radius(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].dir = parse_dir(s);
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void	parse_paraboloid(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 7 : 0;
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
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
	sd->obj[i].m_blur = ft_normalize(parse_m_blur(s));
}

void	parse_ellipsoid(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 6 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].a = parse_a(s);
	sd->obj[i].b = parse_b(s);
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

void	parse_triangle(char *s, int i, t_sdl *sd)
{
	cl_float3	b;
	cl_float3	c;

	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 8 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].c1 = parse_c1(s);
	sd->obj[i].c2 = parse_c2(s);
	b = ft_vector_sub(sd->obj[i].c1, sd->obj[i].pos);
	c = ft_vector_sub(sd->obj[i].c2, sd->obj[i].pos);
	sd->obj[i].dir = ft_normalize((ft_cross(b, c)));
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
}

void	parse_disk(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 10 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = ft_normalize(parse_dir(s));
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].s_radius = parse_s_radius(s);
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
