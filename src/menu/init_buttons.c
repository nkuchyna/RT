/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:48:40 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/07/28 18:48:51 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_edit_line(t_sdl *sd, int *i)
{
	int		line_nbr;
	int		x;
	int		y;

	line_nbr = 1;
	x = 225;
	y = 550;
	while (*i <= 19 && line_nbr <= 3)
	{
		ft_init_places_rect(*i - 1, sd->places, x, y);
		ft_init_line_rect(*i - 1, sd->menu, &x, &y);
		if (*i - (3 * line_nbr) == 10 && line_nbr <= 3)
		{
			y += 15 + 3;
			x = 225;
			line_nbr++;
		}
		(*i)++;
	}
}

void	ft_init_main_line(t_sdl *sd, int *i)
{
	int		line_nbr;
	int		x;
	int		y;

	line_nbr = 1;
	x = 3;
	y = 514;
	while (++(*i) <= 10 && line_nbr <= 3)
	{
		ft_init_places_rect(*i, sd->places, x, y);
		ft_init_line_rect(*i, sd->menu, &x, &y);
		if ((*i + 1) % 5 == 0 && *i != 0)
		{
			y += 15 + 3;
			x = 3;
			line_nbr++;
		}
	}
}

void	ft_init_effect_line(t_sdl *sd, int *i)
{
	int		line_nbr;
	int		x;
	int		y;

	line_nbr = 1;
	x = 76;
	y = 550;
	while (*i <= 31 && line_nbr <= 3)
	{
		ft_init_places_rect(*i - 1, sd->places, x, y);
		ft_init_line_rect(*i - 1, sd->menu, &x, &y);
		if (*i - (4 * line_nbr) == 19 && line_nbr <= 3)
		{
			y += 15 + 3;
			x = 76;
			line_nbr++;
		}
		(*i)++;
	}
}

void	ft_init_scale_ef_line(t_sdl *sd, int *i)
{
	int		line_nbr;
	int		x;
	int		y;

	line_nbr = 1;
	x = 3;
	y = 550;
	while (*i <= 33 && line_nbr <= 3)
	{
		ft_init_places_rect(*i - 1, sd->places, x, y);
		ft_init_line_rect(*i - 1, sd->menu, &x, &y);
		y += 23 + 3;
		x = 3;
		line_nbr++;
		(*i)++;
	}
	x = 320;
	y = 532;
	ft_init_places_rect(*i - 1, sd->places, x, y);
	ft_init_line_rect(*i - 1, sd->menu, &x, &y);
	(*i)++;
}

void	ft_init_system_line(t_sdl *sd, int *i)
{
	int		line_nbr;
	int		x;
	int		y;

	line_nbr = 1;
	x = 370;
	y = 514;
	while (*i <= 37 && line_nbr <= 2)
	{
		ft_init_places_rect(*i - 1, sd->places, x + 8, y + 15);
		ft_init_line_rect(*i - 1, sd->menu, &x, &y);
		y += 42 + 3;
		x = 370;
		line_nbr++;
		(*i)++;
	}
}
