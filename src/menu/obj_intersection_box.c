/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_box.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:49:39 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 10:49:41 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float		ft_check_pnt_box(float min[3], float max[3])
{
	float			t[2];

	if (min[0] > min[1])
		t[0] = min[0];
	else
		t[0] = min[1];
	if (min[2] > t[0])
		t[0] = min[2];
	if (max[0] < max[1])
		t[1] = max[0];
	else
		t[1] = max[1];
	if (max[2] < t[1])
		t[1] = max[2];
	if (t[0] < t[1] && t[1] > T_MIN && t[1] < T_MAX)
	{
		if (t[0] > T_MIN && t[0] < T_MAX)
			min[0] = t[0];
		else
			min[0] = t[1];
		return (min[0]);
	}
	return (T_MAX);
}

static void			ft_swap_min_max(float *min, float *max)
{
	float			temp;

	temp = *min;
	*min = *max;
	*max = temp;
}

float				ft_box_inter(cl_float3 ov, cl_float3 point, t_obj *obj)
{
	float			min[3];
	float			max[3];
	cl_float3		rev_ov;

	rev_ov.x = 1 / ov.x;
	rev_ov.y = 1 / ov.y;
	rev_ov.z = 1 / ov.z;
	min[0] = (obj->pos.x - point.x) * rev_ov.x;
	max[0] = (obj->pos.x + obj->a - point.x) * rev_ov.x;
	if (rev_ov.x < 0)
		ft_swap_min_max(&min[0], &max[0]);
	min[1] = (obj->pos.y - point.y) * rev_ov.y;
	max[1] = (obj->pos.y + obj->b - point.y) * rev_ov.y;
	if (rev_ov.y < 0)
		ft_swap_min_max(&min[1], &max[1]);
	min[2] = (obj->pos.z - point.z) * rev_ov.z;
	max[2] = (obj->pos.z + obj->c - point.z) * rev_ov.z;
	if (rev_ov.z < 0)
		ft_swap_min_max(&min[2], &max[2]);
	return (ft_check_pnt_box(min, max));
}
