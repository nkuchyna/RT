/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_composed.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:43:28 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 10:43:29 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_tunel_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float		t1;
	float		t2;
	float		t_min;
	float		tmp;

	t1 = ft_cylinder_closed_inter(ov, point, obj);
	tmp = obj->radius;
	obj->radius = obj->s_radius;
	t2 = ft_cylinder_inter(ov, point, obj);
	obj->radius = tmp;
	t_min = ft_define_min(t1, t2);
	if (t_min == t2)
		obj->type_inter = 1;
	return (t_min);
}

float			ft_define_bocal_inter(float *t, t_obj *obj)
{
	float		t_min;

	t_min = ft_define_min(t[0], t[1]);
	t_min = ft_define_min(t_min, t[2]);
	t_min = ft_define_min(t_min, t[3]);
	t_min = ft_define_min(t_min, t[4]);
	t_min = ft_define_min(t_min, t[5]);
	t_min = ft_define_min(t_min, t[6]);
	if (t_min == t[0])
		obj->type_inter = 1;
	if (t_min == t[1])
		obj->type_inter = 2;
	if (t_min == t[2])
		obj->type_inter = 3;
	return (t_min);
}

float			ft_bocal_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float		t[3];
	float		tmp_radius;
	float		tmp_height;
	cl_float3	tmp_pos;
	cl_float3	tmp_dir;

	tmp_radius = obj->height * 4 / 30;
	tmp_pos = obj->pos;
	tmp_dir = obj->dir;
	tmp_height = obj->height;
	obj->radius = tmp_radius * 0.1;
	obj->height = tmp_height * 0.4;
	t[0] = ft_cylinder_inter(ov, point, obj);
	obj->pos = ft_vector_add(obj->pos, ft_vector_mult(obj->dir, 0.2));
	obj->dir = ft_vector_mult(obj->dir, -1);
	obj->height = tmp_height * 0.6;
	t[1] = ft_paraboloid_inter(ov, point, obj);
	obj->dir = tmp_dir;
	obj->pos = ft_vector_add(tmp_pos, ft_vector_mult(obj->dir,
	(tmp_height * 0.4f)));
	obj->radius = tmp_radius;
	t[2] = ft_disk_inter(ov, point, obj);
	obj->pos = tmp_pos;
	obj->height = tmp_height;
	return (ft_define_bocal_inter(t, obj));
}

float			ft_cylinder_closed_inter(cl_float3 ov,
										cl_float3 point, t_obj *obj)
{
	float		t_min;
	float		t1;
	float		t2;
	float		t3;
	cl_float3	pos;

	t_min = T_MAX;
	t1 = ft_cylinder_inter(ov, point, obj);
	pos = obj->pos;
	t2 = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t1, t2);
	obj->pos = ft_vector_add(pos, ft_vector_mult(obj->dir, obj->height));
	t3 = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t_min, t3);
	obj->pos = pos;
	if (t_min == t3)
		obj->type_inter = 3;
	else if (t_min == t2)
		obj->type_inter = 2;
	else if (t_min == t1)
		obj->type_inter = 1;
	return (t_min);
}

float			ft_cone_closed_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float		t_min;
	float		t1;
	float		t2;
	cl_float3	pos;

	t_min = T_MAX;
	t1 = ft_cone_inter(ov, point, obj);
	pos = obj->pos;
	obj->pos = ft_vector_add(obj->pos, ft_vector_mult(obj->dir, obj->height));
	obj->radius = obj->height * obj->angle;
	t2 = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t1, t2);
	obj->pos = pos;
	if (t_min == t2)
		obj->type_inter = 2;
	else if (t_min == t1)
		obj->type_inter = 1;
	return (t_min);
}
