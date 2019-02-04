/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrange_tetragon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:58:37 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/07 10:00:47 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_calc_angle(cl_float3 pos, cl_float3 a, cl_float3 b)
{
	cl_float3	ap;
	cl_float3	bp;
	float		angle;

	ap = ft_vector_sub(a, pos);
	bp = ft_vector_sub(b, pos);
	ap = ft_normalize(ap);
	bp = ft_normalize(bp);
	angle = ft_vector_dot(ap, bp);
	angle = acos(angle);
	return (angle);
}

static void		appropriation(t_obj *obj, cl_float3 c1, cl_float3 pos)
{
	obj->c1 = pos;
	obj->pos = c1;
}

void			ft_arrange_el(float angle_max, cl_float3 angle, t_obj *obj)
{
	cl_float3	c1;
	cl_float3	c2;
	cl_float3	c3;
	cl_float3	pos;

	pos = obj->pos;
	c1 = obj->c1;
	c2 = obj->c2;
	c3 = obj->c3;
	if (angle_max == angle.x)
	{
		obj->c1 = pos;
		obj->c2 = c3;
		obj->pos = c1;
		obj->c3 = c2;
	}
	else if (angle_max == angle.y)
	{
		obj->c1 = pos;
		obj->c2 = c1;
		obj->pos = c3;
		obj->c3 = c2;
	}
	else if (angle_max == angle.z)
		appropriation(obj, c1, pos);
}

void			ft_arrange_tetragon(t_obj *obj)
{
	int			i;
	float		angle_max;
	cl_float3	angle;

	angle.x = ft_calc_angle(obj->pos, obj->c1, obj->c2);
	angle.y = ft_calc_angle(obj->pos, obj->c2, obj->c3);
	angle.z = ft_calc_angle(obj->pos, obj->c3, obj->c1);
	i = 1;
	angle_max = angle.x;
	if (angle.y > angle_max)
		angle_max = angle.y;
	if (angle.z > angle_max)
		angle_max = angle.z;
	ft_arrange_el(angle_max, angle, obj);
}
