/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_other_simple.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:43:19 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 10:43:20 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_ellips_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	cl_float3	oc;
	cl_float3	m;
	float		k[3];
	float		c;

	oc = ft_vector_sub(point, obj->pos);
	c = 2 * sqrt(obj->a * obj->a - obj->b * obj->b);
	m.x = 4 * pow(2 * obj->a, 2);
	m.y = 2 * c * ft_vector_dot(ov, obj->dir);
	m.z = pow(2 * obj->a, 2) + 2 * c * ft_vector_dot(oc, obj->dir) - c;
	k[0] = m.x * ft_vector_dot(ov, ov) - m.y * m.y;
	k[1] = 2 * (m.x * ft_vector_dot(ov, oc) - m.y * m.z);
	k[2] = m.x * ft_vector_dot(oc, oc) - m.z * m.z;
	return (ft_solve_quadratic_eq(k[0], k[1], k[2]));
}

float			ft_paraboloid_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	cl_float3	oc;
	cl_float3	k;
	float		t_min;
	float		d_r;

	d_r = 2 * obj->radius;
	oc = ft_vector_sub(point, obj->pos);
	k.x = ft_vector_dot(ov, ov) - ft_vector_dot(ov, obj->dir) *
	ft_vector_dot(ov, obj->dir);
	k.y = 2 * (ft_vector_dot(ov, oc) - ft_vector_dot(ov, obj->dir) *
	(ft_vector_dot(oc, obj->dir) + d_r));
	k.z = ft_vector_dot(oc, oc) - ft_vector_dot(oc, obj->dir) *
	(ft_vector_dot(oc, obj->dir) + 2 * d_r);
	t_min = ft_check_pnt(k, ov, point, obj);
	return (t_min);
}

float			ft_torus_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	int			num;
	float		c[5];
	float		s[4];
	float		t_min;
	cl_float3	oc;

	t_min = T_MAX;
	oc = ft_vector_sub(point, obj->pos);
	obj->radius += obj->s_radius;
	if (ft_sphere_inter(ov, point, obj) == T_MAX)
	{
		obj->radius -= obj->s_radius;
		return (T_MAX);
	}
	obj->radius -= obj->s_radius;
	ft_define_eq_params(c, oc, ov, obj);
	if (!(num = ft_solve_quart_eq(c, s)))
		return (T_MAX);
	t_min = ft_define_torus_t_min(s, num);
	return (t_min);
}

float			ft_triangle_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float		t;
	float		m[2];
	cl_float3	b;
	cl_float3	c;
	cl_float3	p;

	b = ft_vector_sub(obj->c1, obj->pos);
	c = ft_vector_sub(obj->c2, obj->pos);
	obj->dir = ft_normalize((ft_cross(b, c)));
	if ((t = ft_plane_inter(ov, point, obj)) != T_MAX)
	{
		p = ft_vector_add(point, ft_vector_mult(ov, t));
		p = ft_vector_sub(p, obj->pos);
		m[0] = (c.x * p.y - c.y * p.x) / (c.x * b.y - c.y * b.x);
		if (m[0] >= 0 && m[0] <= 1)
		{
			m[1] = (p.x - m[0] * b.x) / c.x;
			if (m[1] >= 0 && (m[0] + m[1]) <= 1)
				return (t);
		}
	}
	return (T_MAX);
}

float			ft_tetragon_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float		t[2];
	float		t_min;
	cl_float3	pos_tmp;
	cl_float3	obj_dir_tmp;

	t_min = T_MAX;
	t[0] = ft_triangle_inter(ov, point, obj);
	pos_tmp = obj->pos;
	obj->pos = obj->c3;
	obj_dir_tmp = obj->dir;
	t[1] = ft_triangle_inter(ov, point, obj);
	if (fabs(ft_vector_dot(obj->dir, obj_dir_tmp)) == 1)
		t_min = ft_define_min(t[0], t[1]);
	if (t_min == t[0])
		obj->dir = obj_dir_tmp;
	obj->pos = pos_tmp;
	return (t_min);
}
