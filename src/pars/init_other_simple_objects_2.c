/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other_simple_objects_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 09:00:25 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 09:00:26 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_tetragon(char *s, int i, t_sdl *sd)
{
	cl_float3	b;
	cl_float3	c;

	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 9 : 0;
	sd->obj[i].cut = 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].c1 = parse_c1(s);
	sd->obj[i].c2 = parse_c2(s);
	sd->obj[i].c3 = parse_c3(s);
	b = ft_vector_sub(sd->obj[i].c1, sd->obj[i].pos);
	c = ft_vector_sub(sd->obj[i].c3, sd->obj[i].pos);
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
	ft_arrange_tetragon(&sd->obj[i]);
}

void	parse_mandelbulb(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 99 : 0;
	sd->obj[i].pos.x = -sd->cam.dir.x * 5;
	sd->obj[i].pos.y = -sd->cam.dir.y * 5;
	sd->obj[i].pos.z = -sd->cam.dir.z * 5;
	sd->obj[i].color = parse_color(s);
}

void	parse_torus88(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 88 : 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].dir = parse_dir(s);
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
}

void	parse_perfcube(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 77 : 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
}

void	parse_heart(char *s, int i, t_sdl *sd)
{
	init_typical_obj(i, sd);
	(check_in(&s)) ? sd->obj[i].id = 69 : 0;
	sd->obj[i].pos = parse_pos(s);
	sd->obj[i].color = parse_color(s);
	sd->obj[i].emission = parse_emission(s);
	sd->obj[i].radius = parse_radius(s);
	sd->obj[i].refraction = parse_refract(s);
	sd->obj[i].diffuse = parse_diffuse(s);
	sd->obj[i].cos_pow = parse_cos_pow(s);
	sd->obj[i].refl_type = parse_material(s);
	sd->obj[i].diffuse = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 2\
	|| sd->obj[i].refl_type == 4 ? 0 : sd->obj[i].diffuse;
	sd->obj[i].cos_pow = sd->obj[i].refl_type == 1 || sd->obj[i].refl_type == 4\
	|| sd->obj[i].refl_type == 5 ? 100000 : sd->obj[i].cos_pow;
}
