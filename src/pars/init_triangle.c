/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:29:48 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 09:08:20 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_triangle(t_obj *obj, cl_float3 *vec, char *s)
{
	cl_float3	b;
	cl_float3	c;

	obj->pos = vec[0];
	obj->c1 = vec[1];
	obj->c2 = vec[2];
	b = ft_vector_sub(obj->c1, obj->pos);
	c = ft_vector_sub(obj->c2, obj->pos);
	obj->dir = ft_normalize((ft_cross(b, c)));
	obj->color = parse_color(s);
	obj->emission = parse_emission(s);
	obj->refraction = parse_refract(s);
	obj->refl_type = parse_material(s);
	obj->cut = 0;
	obj->id = 8;
}

void			init_tetragon(t_obj *obj, cl_float3 *vec,
							char *s, cl_float3 *vec_2)
{
	obj->pos = ft_vector_add(vec[0], *vec_2);
	obj->c1 = ft_vector_add(vec[1], *vec_2);
	obj->c2 = ft_vector_add(vec[2], *vec_2);
	obj->c3 = ft_vector_add(vec[3], *vec_2);
	obj->color = parse_color(s);
	obj->emission = parse_emission(s);
	obj->refraction = parse_refract(s);
	obj->refl_type = parse_material(s);
	obj->cut = 0;
	obj->id = 9;
	ft_arrange_tetragon(obj);
}
