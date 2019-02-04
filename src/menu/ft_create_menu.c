/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 17:00:46 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/07/24 17:01:02 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_define_w_h(int i, int *width, int *height)
{
	if (i == 8 || i == 9 || i == 33)
		*width = 46;
	else if (i > 9 && i < 19)
		*width = 45;
	else if (i >= 19 && i < 31)
		*width = 34;
	else if (i == 31 || i == 32)
		*height = 23;
	else if (i == 34 || i == 35)
	{
		*width = 138;
		*height = 42;
	}
}

void		ft_init_line_rect(int i, SDL_Rect *menu, int *x, int *y)
{
	int		width;
	int		height;

	width = 70;
	height = 15;
	ft_define_w_h(i, &width, &height);
	menu[i].x = *x;
	menu[i].y = *y;
	menu[i].w = width;
	menu[i].h = height;
	if (*x + width > WIDTH)
	{
		*y += height + 3;
		*x = 3;
	}
	*x += width + 3;
}

void		ft_init_places_rect(int i, SDL_Rect *places, int x, int y)
{
	int		shift;

	shift = 10;
	places[i].w = 0;
	places[i].h = 0;
	places[i].y = y - 5;
	if (i == 27 || i == 28)
		shift = 5;
	if (i >= 0 && i <= 7)
		shift = 20;
	if (i == 31 || i == 32)
	{
		shift = 30;
		places[i].y = y;
	}
	if (i == 34 || i == 35)
		shift = 20 + 4;
	places[i].x = x + shift;
}

static void	ft_init_menu_cover(t_sdl *sd)
{
	sd->menu_cover.x = 0;
	sd->menu_cover.y = 512;
	sd->menu_cover.w = 512;
	sd->menu_cover.h = MENU_HEIGHT;
}

void		ft_create_menu(t_sdl *sd)
{
	int		i;

	sd->menu = malloc(sizeof(SDL_Rect) * MENU_RECT_NBR);
	sd->places = malloc(sizeof(SDL_Rect) * MENU_RECT_NBR);
	sd->texts = malloc(sizeof(SDL_Surface*) * MENU_RECT_NBR);
	ft_add_texts(sd);
	sd->s = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
	i = -1;
	ft_init_menu_cover(sd);
	ft_init_main_line(sd, &i);
	ft_init_edit_line(sd, &i);
	ft_init_effect_line(sd, &i);
	ft_init_scale_ef_line(sd, &i);
	ft_init_system_line(sd, &i);
}
