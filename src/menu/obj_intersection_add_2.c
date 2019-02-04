/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 12:58:27 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/16 09:53:27 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_solve_quadratic_eq_base(cl_float3 k, cl_float3 *t)
{
	float		des;

	if ((des = k.y * k.y - 4 * k.x * k.z) >= 0)
	{
		t->x = (-k.y + sqrt(des)) / (2 * k.x);
		t->y = (-k.y - sqrt(des)) / (2 * k.x);
	}
	else
	{
		t->x = T_MAX;
		t->y = T_MAX;
		t->z = T_MAX;
	}
}

float			ft_define_tmin_m(cl_float3 t, float *m, t_obj *obj)
{
	if (t.x >= T_MIN && t.x < T_MAX && t.x < t.z)
	{
		obj->m = m[0];
		t.z = t.x;
	}
	if (t.y >= T_MIN && t.y < T_MAX && t.y < t.z)
	{
		obj->m = m[1];
		t.z = t.y;
	}
	return (t.z);
}

static void		part_of_chk_pnt(t_obj *obj, cl_float3 *ac, float m,
								cl_float3 *t)
{
	*ac = ft_vector_sub(obj->pos, obj->pos);
	*ac = ft_vector_add(*ac, ft_vector_mult(obj->dir, m));
	obj->len_ac = ft_vector_len(*ac);
	(obj->height != 0 && (obj->len_ac > obj->height ||
	ft_vector_dot(*ac, obj->dir) < 0)) ? (t->x = T_MAX) : 0;
}

float			ft_check_pnt(cl_float3 k, cl_float3 ov,
				cl_float3 point, t_obj *obj)
{
	cl_float3	t;
	cl_float3	ac;
	cl_float3	oc;
	float		m[2];

	t.z = T_MAX;
	oc = ft_vector_sub(point, obj->pos);
	ft_solve_quadratic_eq_base(k, &t);
	if (t.x == T_MAX && t.y == T_MAX && t.z == T_MAX)
		return (T_MAX);
	m[0] = (ft_vector_dot(ov, obj->dir) * t.x) + ft_vector_dot(oc, obj->dir);
	part_of_chk_pnt(obj, &ac, m[0], &t);
	(t.x != T_MAX && obj->cut != 0) ? (t.x = ft_check_cut(t.x, obj,
	ft_vector_add(point, ft_vector_mult(ov, t.x)))) : 0;
	m[1] = (ft_vector_dot(ov, obj->dir) * t.y) + ft_vector_dot(oc, obj->dir);
	ac = ft_vector_sub(obj->pos, obj->pos);
	ac = ft_vector_add(ac, ft_vector_mult(obj->dir, m[1]));
	obj->len_ac = ft_vector_len(ac);
	(obj->height != 0 && (obj->len_ac > obj->height ||
	ft_vector_dot(ac, obj->dir) < 0)) ? (t.y = T_MAX) : 0;
	(t.y != T_MAX && obj->cut != 0) ? (t.y = ft_check_cut(t.y, obj,
	ft_vector_add(point, ft_vector_mult(ov, t.y)))) : 0;
	t.z = ft_define_tmin_m(t, m, obj);
	return (t.z);
}

int				ft_cut_plane(float t, t_obj *obj, cl_float3 point, cl_float3 ov)
{
	cl_float3	p;
	cl_float3	cut_plane_pos;
	cl_float3	pc;

	p = ft_vector_add(point, ft_vector_mult(ov, t));
	cut_plane_pos = ft_vector_add(obj->pos, obj->cut_shift);
	pc = ft_vector_sub(p, cut_plane_pos);
	if (ft_vector_dot(obj->cut_dir, pc) >= 0)
		return (1);
	return (0);
}
