/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 17:46:01 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/07/27 17:46:05 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	ft_choose_obj2(t_obj *obj, cl_float3 o, cl_float3 d, int i)
{
	float		t;

	t = 0;
	if (obj[i].id == 8)
		t = ft_triangle_inter(d, o, &obj[i]);
	else if (obj[i].id == 9)
		t = ft_tetragon_inter(d, o, &obj[i]);
	else if (obj[i].id == 10)
		t = ft_disk_inter(d, o, &obj[i]);
	else if (obj[i].id == 11)
		t = ft_tunel_inter(d, o, &obj[i]);
	else if (obj[i].id == 12)
		t = ft_bocal_inter(d, o, &obj[i]);
	else if (obj[i].id == 31)
		t = ft_cylinder_closed_inter(d, o, &obj[i]);
	else if (obj[i].id == 41)
		t = ft_cone_closed_inter(d, o, &obj[i]);
	else if (obj[i].id == 13)
		t = ft_box_inter(d, o, &obj[i]);
	return (t);
}

float	ft_choose_obj1(t_obj *obj, cl_float3 o, cl_float3 d, int i)
{
	float		t;

	t = 0;
	if (obj[i].id == 1)
		t = ft_plane_inter(d, o, &obj[i]);
	else if (obj[i].id == 2)
		t = ft_sphere_inter(d, o, &obj[i]);
	else if (obj[i].id == 3)
		t = ft_cylinder_inter(d, o, &obj[i]);
	else if (obj[i].id == 4)
		t = ft_cone_inter(d, o, &obj[i]);
	else if (obj[i].id == 5)
		t = ft_torus_inter(d, o, &obj[i]);
	else if (obj[i].id == 6)
		t = ft_ellips_inter(d, o, &obj[i]);
	else if (obj[i].id == 7)
		t = ft_paraboloid_inter(d, o, &obj[i]);
	else if ((obj[i].id >= 8 && obj[i].id <= 12) || obj[i].id == 31
	|| obj[i].id == 41 || obj[i].id == 13)
		t = ft_choose_obj2(obj, o, d, i);
	return (t);
}

int		intersection(t_obj *obj, cl_float3 o, cl_float3 d)
{
	int		i;
	int		id;
	float	t;
	float	t_fin;

	i = 0;
	t = 0;
	t_fin = T_MAX;
	id = -1;
	while (i < obj[0].count)
	{
		t = ft_choose_obj1(obj, o, d, i);
		if (t >= T_MIN && t < t_fin)
		{
			t_fin = t;
			id = i;
		}
		i++;
	}
	return (id);
}

int		ft_choose_obj(t_sdl *sd, int x, int y)
{
	float		vplane_half_w;
	float		vplane_half_h;
	cl_float3	dir;
	cl_float3	b_point;
	t_render	r;

	r.cx.y = 0;
	r.cx.z = 0;
	dir.x = 0;
	dir.y = 1;
	dir.z = 0;
	r.cx = ft_normalize(ft_cross(sd->cam.dir, dir));
	r.cy = ft_normalize(ft_cross(r.cx, sd->cam.dir));
	r.cy = ft_vector_mult(r.cy, -1);
	vplane_half_w = tan(0.261799f);
	vplane_half_h = HEIGHT / WIDTH * vplane_half_w;
	b_point = ft_vector_add(sd->cam.pos, sd->cam.dir);
	b_point = ft_vector_sub(b_point, ft_vector_mult(r.cy, vplane_half_h));
	b_point = ft_vector_sub(b_point, ft_vector_mult(r.cx, vplane_half_w));
	r.cx = ft_vector_mult(r.cx, 2 * vplane_half_w / WIDTH);
	r.cy = ft_vector_mult(r.cy, 2 * vplane_half_h / HEIGHT);
	r.ray = ft_vector_add(b_point, ft_vector_mult(r.cx, x));
	r.ray = ft_vector_add(r.ray, ft_vector_mult(r.cy, y));
	r.ray = ft_normalize(ft_vector_sub(r.ray, sd->cam.pos));
	return (intersection(sd->obj, sd->cam.pos, r.ray));
}
