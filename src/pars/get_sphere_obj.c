/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:26:57 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/16 11:26:58 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_sphere(t_obj *sphere, cl_float3 min, cl_float3 max)
{
	if (sphere)
	{
		sphere->id = 14;
		sphere->cut = 0;
		sphere->pos = ft_vector_add(min,
		ft_vector_mult((ft_vector_sub(max, min)), 0.5));
		sphere->radius = ft_vector_len(ft_vector_sub(max, min)) / 2 - 25;
	}
	else
		ft_putstr("Not enough memory to allocate sphere!\n");
}

static void		get_max_min(cl_float3 *max, cl_float3 *min, t_o *o, int count)
{
	int i;

	i = 1;
	while (i < count)
	{
		if (o->v[i].x > max->x)
			max->x = o->v[i].x;
		if (o->v[i].x < min->x)
			min->x = o->v[i].x;
		if (o->v[i].y > max->y)
			max->y = o->v[i].y;
		if (o->v[i].y < min->y)
			min->y = o->v[i].y;
		if (o->v[i].z > max->z)
			max->z = o->v[i].z;
		if (o->v[i].z < min->z)
			min->z = o->v[i].z;
		i++;
	}
}

t_obj			*get_sphere(int count, t_o *o)
{
	t_obj		*sphere;
	cl_float3	max;
	cl_float3	min;

	sphere = (t_obj *)ft_memalloc(sizeof(t_obj));
	max = o->v[0];
	min = o->v[0];
	get_max_min(&max, &min, o, count);
	init_sphere(sphere, min, max);
	return (sphere);
}
