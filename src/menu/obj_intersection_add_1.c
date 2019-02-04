/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_add_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:23:25 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 11:23:30 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_define_min(float t1, float t2)
{
	float		t_min;

	t_min = T_MAX;
	if (t1 >= T_MIN && t1 < T_MAX && t1 < t_min)
		t_min = t1;
	if (t2 >= T_MIN && t2 < T_MAX && t2 < t_min)
		t_min = t2;
	return (t_min);
}

float			ft_check_cut(float t_min, t_obj *obj, cl_float3 p)
{
	cl_float3	cut_plane_pos;
	cl_float3	pc;

	cut_plane_pos = ft_vector_add(obj->pos, obj->cut_shift);
	pc = ft_vector_sub(p, cut_plane_pos);
	if (ft_vector_dot(obj->cut_dir, pc) >= 0)
		t_min = T_MAX;
	return (t_min);
}

float			ft_define_torus_t_min(float *s, int num)
{
	int			i;
	float		t_min;

	t_min = T_MAX;
	i = 0;
	while (i < num)
	{
		if (s[i] >= T_MIN && s[i] < T_MAX && s[i] < t_min)
			t_min = s[i];
		i++;
	}
	return (t_min);
}

void			ft_define_eq_params(float *c, cl_float3 oc, cl_float3 ov,
									t_obj *obj)
{
	float		r1;
	float		r2;
	float		m[4];
	float		k[4];

	r1 = obj->radius * obj->radius;
	r2 = obj->s_radius * obj->s_radius;
	m[0] = ft_vector_dot(ov, oc);
	m[1] = ft_vector_dot(oc, oc);
	m[2] = ft_vector_dot(obj->dir, oc);
	m[3] = ft_vector_dot(obj->dir, ov);
	k[0] = 1 - m[3] * m[3];
	k[1] = 2 * (ft_vector_dot(oc, ov) - m[2] * m[3]);
	k[2] = m[1] - m[2] * m[2];
	k[3] = m[1] + r1 - r2;
	c[4] = 1;
	c[3] = 4 * m[0];
	c[2] = 2 * k[3] + c[3] * c[3] * 0.25f - 4 * r1 * k[0];
	c[1] = c[3] * k[3] - 4 * r1 * k[1];
	c[0] = k[3] * k[3] - 4 * r1 * k[2];
}

float			ft_solve_quadratic_eq(float k1, float k2, float k3)
{
	float		des;
	float		t1;
	float		t2;
	float		t_min;

	t_min = T_MAX;
	if ((des = k2 * k2 - 4 * k1 * k3) >= 0)
	{
		t1 = (-k2 + sqrt(des)) / (2 * k1);
		t2 = (-k2 - sqrt(des)) / (2 * k1);
		if (t1 >= T_MIN && t1 < T_MAX && t1 < t_min)
			t_min = t1;
		if (t2 >= T_MIN && t2 < T_MAX && t2 < t_min)
			t_min = t2;
	}
	return (t_min);
}
