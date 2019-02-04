/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_typical_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:19:11 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/25 10:19:12 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_float3_data_obj(int i, t_sdl *sd)
{
	sd->obj[i].pos = (cl_float3){{0, 0, 0}};
	sd->obj[i].dir = (cl_float3){{0, 0, 0}};
	sd->obj[i].color = (cl_float3){{1, 1, 1}};
	sd->obj[i].emission = (cl_float3){{0, 0, 0}};
	sd->obj[i].c1 = (cl_float3){{0, 0, 0}};
	sd->obj[i].c2 = (cl_float3){{0, 0, 0}};
	sd->obj[i].c3 = (cl_float3){{0, 0, 0}};
	sd->obj[i].cut_dir = (cl_float3){{0, 0, 0}};
	sd->obj[i].cut_shift = (cl_float3){{0, 0, 0}};
	sd->obj[i].obj_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].text_rotation = (cl_float3){{0, 0, 0}};
	sd->obj[i].negative = 0;
	sd->obj[i].m_blur = (cl_float3){{0, 0, 0}};
}

void			init_typical_obj(int i, t_sdl *sd)
{
	init_float3_data_obj(i, sd);
	sd->obj[i].diffuse = (float)1;
	sd->obj[i].refraction = (float)1.5;
	sd->obj[i].s_radius = (float)0;
	sd->obj[i].radius = (float)10;
	sd->obj[i].angle = (float)1;
	sd->obj[i].c = (float)0;
	sd->obj[i].height = (float)20;
	sd->obj[i].a = (float)0;
	sd->obj[i].b = (float)0;
	sd->obj[i].m = (float)0;
	sd->obj[i].len_ac = (float)0;
	sd->obj[i].cos_pow = (float)100000;
	sd->obj[i].count = (int)0;
	sd->obj[i].type_inter = (int)0;
	sd->obj[i].cut = (int)0;
	sd->obj[i].id = (int)0;
	sd->obj[i].texture = -1;
	sd->obj[i].bump = -1;
	sd->obj[i].pattern = -1;
	sd->obj[i].tscale = 1;
}
