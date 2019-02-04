/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 15:49:54 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/07 15:49:56 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			init_cl_start(t_sdl *sd)
{
	FILE		*fd;
	size_t		program_size;

	fd = fopen("./src/open_cl/pathtracer.cl", "rb");
	(!fd) ? ft_putendl("Failed to load kernel") : 0;
	fseek(fd, 0, SEEK_END);
	program_size = ftell(fd);
	rewind(fd);
	sd->source_str = (char*)malloc(program_size + 1);
	sd->source_str[program_size] = '\0';
	fread(sd->source_str, sizeof(char), program_size, fd);
	fclose(fd);
	sd->err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &sd->device_id, NULL);
	(sd->err != CL_SUCCESS) ? error(1, sd) : 0;
	sd->context = clCreateContext(0, 1, &sd->device_id, NULL, NULL, &sd->err);
	(!sd->context) ? error(2, sd) : 0;
	sd->commands = clCreateCommandQueue(sd->context, sd->device_id, 0,
	&sd->err);
	(!sd->commands) ? error(3, sd) : 0;
	sd->program = clCreateProgramWithSource(sd->context, 1,
	(const char **)&sd->source_str, &program_size, &sd->err);
	(!sd->program) ? error(4, sd) : 0;
}

static void			init_cl_create_pro_and_buffs(t_sdl *sd, int n)
{
	free(sd->source_str);
	sd->err = clBuildProgram(sd->program, 0, NULL, NULL, NULL, NULL);
	(sd->err != CL_SUCCESS) ? error(5, sd) : 0;
	sd->kernel = clCreateKernel(sd->program, "pathtracer", &sd->err);
	(!sd->kernel || sd->err != CL_SUCCESS) ? (error(6, sd)) : 0;
	sd->objc = clCreateBuffer(sd->context, CL_MEM_READ_WRITE,
	sizeof(t_obj) * sd->obj[0].count, NULL, NULL);
	sd->lightc = clCreateBuffer(sd->context, CL_MEM_READ_ONLY,
	sizeof(t_light) * sd->light[0].n, NULL, NULL);
	sd->screenc = clCreateBuffer(sd->context, CL_MEM_READ_ONLY,
	sizeof(cl_float3) * n, NULL, NULL);
	(!sd->objc || !sd->lightc || !sd->screenc) ? error(7, sd) : 0;
}

static void			init_desc(t_sdl *sd, cl_image_desc *desc)
{
	desc->image_type = CL_MEM_OBJECT_IMAGE2D;
	desc->image_width = (size_t)sd->texture1->w;
	desc->image_height = (size_t)sd->texture1->h;
	desc->image_depth = 0;
	desc->image_array_size = 1;
	desc->image_row_pitch = 0;
	desc->image_slice_pitch = 0;
	desc->num_mip_levels = 0;
	desc->num_samples = 0;
}

static void			init_cl_create_img(t_sdl *sd)
{
	cl_image_format	format;
	cl_image_desc	desc;

	format.image_channel_data_type = CL_UNORM_INT8;
	format.image_channel_order = CL_RGB;
	desc.buffer = NULL;
	init_desc(sd, &desc);
	sd->texturec1 = clCreateImage(sd->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, &format, &desc, sd->texture1->pixels, &sd->err);
	desc.image_width = (size_t)sd->texture2->w;
	desc.image_height = (size_t)sd->texture2->h;
	sd->texturec2 = clCreateImage(sd->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, &format, &desc, sd->texture2->pixels, &sd->err);
	desc.image_width = (size_t)sd->texture3->w;
	desc.image_height = (size_t)sd->texture3->h;
	sd->texturec3 = clCreateImage(sd->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, &format, &desc, sd->texture3->pixels, &sd->err);
	desc.image_width = (size_t)sd->texture4->w;
	desc.image_height = (size_t)sd->texture4->h;
	sd->texturec4 = clCreateImage(sd->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, &format, &desc, sd->texture4->pixels, &sd->err);
}

void				init_cl(t_sdl *sd)
{
	int n;

	n = WIDTH * HEIGHT;
	init_cl_start(sd);
	init_cl_create_pro_and_buffs(sd, n);
	init_cl_create_img(sd);
}
