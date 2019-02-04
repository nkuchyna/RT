/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalc_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 16:53:43 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/07/07 16:53:59 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_define_cut_dir(t_obj *obj)
{
	if (obj->cut >= -3 && obj->cut <= 3 && obj->cut != 0)
	{
		if (obj->cut == 1 || obj->cut == -1)
			obj->cut_dir = (cl_float3){{1, 0, 0}};
		else if (obj->cut == 2 || obj->cut == -2)
			obj->cut_dir = (cl_float3){{0, 1, 0}};
		else if (obj->cut == 3 || obj->cut == -3)
			obj->cut_dir = (cl_float3){{0, 0, 1}};
		if (obj->cut > 0)
			obj->cut_dir = ft_vector_mult(obj->cut_dir, -1);
	}
}

cl_float3	ft_rotate_vector(cl_float3 obj_rotation, cl_float3 dir)
{
	float	y;
	float	z;
	float	x1;
	float	z1;

	y = (dir.y) * cos(obj_rotation.x) + (dir.z) * sin(obj_rotation.x);
	z = (dir.z) * cos(obj_rotation.x) - (dir.y) * sin(obj_rotation.x);
	x1 = (dir.x) * cos(obj_rotation.y) + z * sin(obj_rotation.y);
	z1 = z * cos(obj_rotation.y) - (dir.x) * sin(obj_rotation.y);
	(dir.x) = x1 * cos(obj_rotation.z) - y * sin(obj_rotation.z);
	(dir.y) = x1 * sin(obj_rotation.z) + y * cos(obj_rotation.z);
	(dir.z) = z1;
	return (dir);
}

void		ft_precalc_params(t_obj *obj)
{
	if (obj->cut != 0 && obj->cut_dir.x == 0
	&& obj->cut_dir.y == 0 && obj->cut_dir.z == 0)
		ft_define_cut_dir(obj);
	obj->dir = ft_rotate_vector(obj->obj_rotation, obj->dir);
	obj->dir = ft_normalize(obj->dir);
	obj->cut_dir = ft_rotate_vector(obj->obj_rotation, obj->cut_dir);
	obj->cut_dir = ft_normalize(obj->cut_dir);
	obj->cut_shift = ft_rotate_vector(obj->obj_rotation, obj->cut_shift);
}
