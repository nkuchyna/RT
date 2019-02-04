/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 14:28:34 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/07 14:28:36 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		build_program_info_e_5(t_sdl *sd)
{
	size_t		len;
	char		buffer[2048];

	ft_putendl("Error: Failed to build program executable!");
	clGetProgramBuildInfo(sd->program, sd->device_id,
	CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
	ft_putendl(buffer);
}

static void		allocate_device_mem_info_e_7(t_sdl *sd)
{
	size_t		len;
	char		buffer[2048];

	ft_putendl("Error: Failed to allocate device memory!");
	clGetProgramBuildInfo(sd->program, sd->device_id,
	CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
	ft_putendl(buffer);
}

static void		errors_10_12(cl_int e)
{
	if (e == 10)
		ft_putendl("Error: Failed to retrieve kernel work group info!");
	else if (e == 11)
		ft_putendl("Error: Failed to execute kernel!");
	else if (e == 12)
		ft_putendl("Error: Failed to read output array!");
}

void			error(cl_int e, t_sdl *sd)
{
	if (e == 1)
		ft_putendl("Error: Failed to create a device group!");
	else if (e == 2)
		ft_putendl("Error: Failed to create a compute context!");
	else if (e == 3)
		ft_putendl("Error: Failed to create a command commands!");
	else if (e == 4)
		ft_putendl("Error: Failed to create compute program!");
	else if (e == 5)
		build_program_info_e_5(sd);
	else if (e == 6)
		ft_putendl("Error: Failed to create compute kernel!");
	else if (e == 7)
		allocate_device_mem_info_e_7(sd);
	else if (e == 8)
		ft_putendl("Error: Failed to write to source array!");
	else if (e == 9)
		ft_putendl("Error: Failed to set kernel arguments");
	else
		errors_10_12(e);
}
