/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_mandator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:43:12 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 10:43:13 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_plane_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	cl_float3	oc;
	float		k1;
	float		k2;
	float		koef;
	float		t;

	oc = ft_vector_sub(point, obj->pos);
	koef = 1;
	t = T_MAX;
	if ((k1 = ft_vector_dot(ov, obj->dir)) == 0)
		return (t);
	k2 = ft_vector_dot(oc, obj->dir);
	if (k1 == k2)
		koef = -1;
	t = -k2 / k1 * koef;
	if (obj->cut != 0 && ft_cut_plane(t, obj, point, ov))
		t = T_MAX;
	return (t);
}

float			ft_sphere_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	cl_float3	oc;
	cl_float3	k;
	float		t_min;

	oc = ft_vector_sub(point, obj->pos);
	k.x = ft_vector_dot(ov, ov);
	k.y = 2 * ft_vector_dot(oc, ov);
	k.z = ft_vector_dot(oc, oc) - obj->radius * obj->radius;
	if (obj->cut != 0)
		t_min = ft_check_pnt(k, ov, point, obj);
	else
		t_min = ft_solve_quadratic_eq(k.x, k.y, k.z);
	return (t_min);
}

float			ft_cone_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	cl_float3	oc;
	cl_float3	k;
	float		a;
	float		t_min;

	oc = ft_vector_sub(point, obj->pos);
	a = 1 + obj->angle * obj->angle;
	k.x = ft_vector_dot(ov, ov) - a * pow(ft_vector_dot(ov, obj->dir), 2);
	k.y = 2 * (ft_vector_dot(ov, oc) - a * ft_vector_dot(ov, obj->dir) *
	ft_vector_dot(oc, obj->dir));
	k.z = ft_vector_dot(oc, oc) - a * pow(ft_vector_dot(oc, obj->dir), 2);
	t_min = ft_check_pnt(k, ov, point, obj);
	return (t_min);
}

float			ft_cylinder_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	cl_float3	oc;
	cl_float3	k;
	float		t_min;

	oc = ft_vector_sub(point, obj->pos);
	k.x = ft_vector_dot(ov, ov) - pow(ft_vector_dot(ov, obj->dir), 2);
	k.y = 2 * (ft_vector_dot(ov, oc) - ft_vector_dot(ov, obj->dir) *
	ft_vector_dot(oc, obj->dir));
	k.z = ft_vector_dot(oc, oc) - pow(ft_vector_dot(oc, obj->dir), 2) -
	obj->radius * obj->radius;
	t_min = ft_check_pnt(k, ov, point, obj);
	return (t_min);
}

float			ft_disk_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float		len;
	float		t;
	cl_float3	p;
	cl_float3	pc;

	t = ft_plane_inter(ov, point, obj);
	p = ft_vector_add(point, ft_vector_mult(ov, t));
	pc = ft_vector_sub(p, obj->pos);
	len = ft_vector_len(pc);
	if (len > obj->radius || len < obj->s_radius || len <= 0)
		(t) = T_MAX;
	return (t);
}
