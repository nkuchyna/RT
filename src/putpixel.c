/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:22:13 by vmartynu          #+#    #+#             */
/*   Updated: 2018/05/30 16:09:06 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float		toint(float x)
{
	float	c;

	if (x < 0)
		x = 0;
	else
	{
		if (x > 1)
			x = 1;
	}
	c = (pow(x, 1 / 2.2) * 255 + 0.5);
	return (c);
}

void				ft_putpixel(t_sdl *sd, cl_float3 color, int i, int pt)
{
	unsigned char	*ptr;
	float			k;

	if (pt)
	{
		k = SAMPS;
		SDL_LockSurface(sd->screen);
		ptr = (unsigned char*)sd->screen->pixels;
		ptr[i++] = toint(color.z * (k / (pt + 1)));
		ptr[i++] = toint(color.y * (k / (pt + 1)));
		ptr[i++] = toint(color.x * (k / (pt + 1)));
		SDL_UnlockSurface(sd->screen);
	}
}
