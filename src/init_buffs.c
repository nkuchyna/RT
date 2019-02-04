/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 16:39:08 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/07 17:15:36 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_enque_buffs(t_sdl *sd, int n)
{
	sd->err = clEnqueueWriteBuffer(sd->commands, sd->objc, CL_TRUE, 0,
	sizeof(t_obj) * sd->obj[0].count, sd->obj, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
	sd->err = clEnqueueWriteBuffer(sd->commands, sd->lightc, CL_TRUE, 0,
	sizeof(t_light) * sd->light[0].n, sd->light, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
	sd->err = clEnqueueWriteBuffer(sd->commands, sd->screenc, CL_TRUE, 0,
	sizeof(cl_float3) * n, sd->color, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
}

static void		init_arr_arr(size_t regions[5][3], t_sdl *sd)
{
	regions[0][0] = 0;
	regions[0][1] = 0;
	regions[0][2] = 0;
	regions[1][0] = sd->texture1->w;
	regions[1][1] = sd->texture1->h;
	regions[1][2] = 1;
	regions[2][0] = sd->texture1->w;
	regions[2][1] = sd->texture1->h;
	regions[2][2] = 1;
	regions[3][0] = sd->texture1->w;
	regions[3][1] = sd->texture1->h;
	regions[3][2] = 1;
	regions[4][0] = sd->texture1->w;
	regions[4][1] = sd->texture1->h;
	regions[4][2] = 1;
}

void			cl_enqueue_image(t_sdl *sd)
{
	size_t		regions[5][3];

	init_arr_arr(regions, sd);
	sd->err = clEnqueueWriteImage(sd->commands, sd->texturec1, CL_TRUE,
	regions[0], regions[1], 0, 0, sd->texture1->pixels, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
	sd->err = clEnqueueWriteImage(sd->commands, sd->texturec2, CL_TRUE,
	regions[0], regions[2], 0, 0, sd->texture2->pixels, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
	sd->err = clEnqueueWriteImage(sd->commands, sd->texturec3, CL_TRUE,
	regions[0], regions[3], 0, 0, sd->texture3->pixels, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
	sd->err = clEnqueueWriteImage(sd->commands, sd->texturec4, CL_TRUE,
	regions[0], regions[4], 0, 0, sd->texture4->pixels, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(8, sd) : 0;
	sd->err = 0;
}

void			init_buffs(t_sdl *sd, int n, int s)
{
	if (s == 0)
		clear_buf(sd->color);
	cl_enque_buffs(sd, n);
	sd->number = rand();
	sd->err = clSetKernelArg(sd->kernel, 0, sizeof(cl_mem), &sd->objc);
	sd->err = clSetKernelArg(sd->kernel, 1, sizeof(cl_mem), &sd->lightc);
	sd->err = clSetKernelArg(sd->kernel, 2, sizeof(cl_float), &sd->ambient);
	sd->err = clSetKernelArg(sd->kernel, 3, sizeof(t_cam), &sd->cam);
	sd->err = clSetKernelArg(sd->kernel, 4, sizeof(cl_mem), &sd->screenc);
	sd->err = clSetKernelArg(sd->kernel, 5, sizeof(unsigned int), &sd->number);
	sd->err = clSetKernelArg(sd->kernel, 6, sizeof(int), &sd->neg);
	sd->err = clSetKernelArg(sd->kernel, 7, sizeof(cl_mem), &sd->texturec1);
	sd->err = clSetKernelArg(sd->kernel, 8, sizeof(cl_mem), &sd->texturec2);
	sd->err = clSetKernelArg(sd->kernel, 9, sizeof(cl_mem), &sd->texturec3);
	sd->err = clSetKernelArg(sd->kernel, 10, sizeof(cl_mem), &sd->texturec4);
	(sd->err != CL_SUCCESS) ? error(9, sd) : 0;
}
