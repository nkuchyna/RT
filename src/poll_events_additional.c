/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_events_additional.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:57:40 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 15:57:41 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		clear_buf(cl_float3 *color)
{
	int		i;

	i = -1;
	while (++i < WIDTH * HEIGHT)
	{
		color[i].x = 0;
		color[i].y = 0;
		color[i].z = 0;
	}
}

cl_float3	mousemot(cl_float3 dir)
{
	int			x;
	int			y;
	cl_float3	angle;
	cl_float3	view;

	view.x = 0;
	view.y = 0;
	view.z = -1;
	SDL_GetRelativeMouseState(&x, &y);
	if (x > 100)
		x = 100;
	else if (x < -100)
		x = -100;
	if (y > 100)
		y = 100;
	else if (y < -100)
		y = -100;
	angle.x = y * 0.01;
	angle.y = -x * 0.01;
	(ft_vector_dot(dir, view) < 0) ? (angle.x = -angle.x) : 0;
	return (angle);
}

char		*ft_change_text_str(int i)
{
	char	*samples_nbr;
	char	*tmp;

	samples_nbr = ft_itoa(i);
	tmp = ft_strjoin("Samples: ", samples_nbr);
	ft_strdel(&samples_nbr);
	return (tmp);
}

void		ft_free_text_surf(SDL_Surface **texts)
{
	int			i;

	i = -1;
	while (++i < MENU_RECT_NBR)
		SDL_FreeSurface(texts[i]);
	free(texts);
}
