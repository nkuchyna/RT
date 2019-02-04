/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_obj_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:54:59 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/02 17:55:02 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	ft_increase_col_comp(float color, int k, float step)
{
	color += step * k;
	if (color > 1)
		color = 1;
	else if (color < 0)
		color = 0;
	return (color);
}

static void		ft_change_rot(float *angle, int k, float shift,
									float *text_r)
{
	if (k == 1)
		*angle = shift;
	if (k == -1)
		*angle = 2 * M_PI - shift;
	*text_r += shift * k;
	if (*text_r > 2 * M_PI)
		*text_r += -2 * M_PI;
	else if (*text_r < 0)
		*text_r += 2 * M_PI;
}

static void		ft_change_col_or_rot(int c, int id_param, t_obj *obj, int k)
{
	if (id_param == 14)
	{
		if (c == 1)
			ft_change_rot(&obj->obj_rotation.x, k, 0.3, &obj->text_rotation.x);
		else if (c == 2)
			ft_change_rot(&obj->obj_rotation.y, k, 0.3, &obj->text_rotation.y);
		else if (c == 3)
			ft_change_rot(&obj->obj_rotation.z, k, 0.3, &obj->text_rotation.z);
		obj->dir = ft_rotate_vector(obj->obj_rotation, obj->dir);
		obj->dir = ft_normalize(obj->dir);
		obj->cut_dir = ft_rotate_vector(obj->obj_rotation, obj->cut_dir);
		obj->cut_dir = ft_normalize(obj->cut_dir);
		obj->cut_shift = ft_rotate_vector(obj->obj_rotation, obj->cut_shift);
	}
	else if (id_param == 15)
	{
		if (c == 1)
			obj->color.x = ft_increase_col_comp(obj->color.x, k, 0.05);
		else if (c == 2)
			obj->color.y = ft_increase_col_comp(obj->color.y, k, 0.05);
		else if (c == 3)
			obj->color.z = ft_increase_col_comp(obj->color.z, k, 0.05);
	}
}

static void		ft_change_obj_pos(int c, t_obj *obj, int k, float shift)
{
	cl_float3		shifted_point;

	shifted_point = obj->pos;
	if (obj->id != 8 && obj->id != 9)
	{
		if (c == 1)
			shifted_point.x += shift * k;
		else if (c == 2)
			shifted_point.y += shift * k;
		else if (c == 3)
			shifted_point.z += shift * k;
		obj->pos = shifted_point;
	}
}

void			ft_change_obj_params(t_obj *obj, int id, int id_param)
{
	int		k;
	int		change_comp;

	obj->obj_rotation.x = 0;
	obj->obj_rotation.y = 0;
	obj->obj_rotation.z = 0;
	change_comp = 0;
	if (id == 10 || id == 12)
		change_comp = 1;
	else if (id == 13 || id == 15)
		change_comp = 2;
	else if (id == 16 || id == 18)
		change_comp = 3;
	if (id == 10 || id == 13 || id == 16 || id == 32)
		k = -1;
	if (id == 12 || id == 15 || id == 18 || id == 31)
		k = 1;
	if (id_param == 13)
		ft_change_obj_pos(change_comp, obj, k, 5);
	if (id_param == 14 || id_param == 15)
		ft_change_col_or_rot(change_comp, id_param, obj, k);
	if (id_param >= 1 && id_param <= 6)
		ft_change_obj_mater(k, id, id_param, obj);
	if (id_param >= 7 && id_param <= 12)
		ft_change_obj_texture(id_param, obj);
}
