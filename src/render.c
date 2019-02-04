/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:10:58 by vmartynu          #+#    #+#             */
/*   Updated: 2018/06/04 15:54:43 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		draw_scene(t_sdl *sd, int pt)
{
	int			i;
	int			index;
	cl_float3	draw_color;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		index = i % WIDTH * 4 + i / WIDTH * sd->screen->pitch;
		if (sd->effect != -1 && sd->effect != 3)
			draw_color = ft_add_color_effect(sd->effect, sd->color[i]);
		else
			draw_color = sd->color[i];
		if (i > WIDTH * HEIGHT)
			break ;
		ft_putpixel(sd, draw_color, index, pt);
		i++;
	}
}

void			render(t_sdl *sd, int pt)
{
	int			n;

	n = HEIGHT * WIDTH;
	sd->err = clEnqueueNDRangeKernel(sd->commands, sd->kernel, 1, NULL,
	&sd->global, &sd->local, 0, NULL, NULL);
	(sd->err) ? (error(11, sd)) : 0;
	clFinish(sd->commands);
	sd->err = clEnqueueReadBuffer(sd->commands, sd->screenc, CL_TRUE, 0,
	sizeof(cl_float3) * n, sd->color, 0, NULL, NULL);
	(sd->err != CL_SUCCESS) ? (error(12, sd)) : 0;
	draw_scene(sd, pt);
	if (sd->effect == 3)
		cartoon(sd);
	ft_add_menu(sd);
	SDL_UpdateWindowSurface(sd->window);
}
