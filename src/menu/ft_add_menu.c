/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:36:29 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/07/31 13:36:59 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_color_main_par_button(int id, t_sdl *sd)
{
	int		main_button_id;

	main_button_id = -1;
	if (id == 19 || id == 20 || id == 23
	|| id == 24 || id == 27 || id == 28)
		main_button_id = 6;
	else if (id == 21 || id == 22 || id == 25
	|| id == 26 || id == 29 || id == 30 || id == 31)
		main_button_id = 7;
	if (main_button_id != -1)
		SDL_FillRect(sd->screen, &sd->menu[main_button_id],
		SDL_MapRGB(sd->s->format, 89, 90, 84));
}

void	ft_add_text(t_sdl *sd)
{
	int				i;

	i = -1;
	while (++i < MENU_RECT_NBR)
		SDL_BlitSurface(sd->texts[i], NULL, sd->screen, &sd->places[i]);
}

void	ft_add_menu(t_sdl *sd)
{
	int			button_id;

	button_id = sd->id_sel_rect;
	SDL_FillRect(sd->screen, &sd->menu_cover,
					SDL_MapRGB(sd->s->format, 69, 70, 64));
	SDL_FillRects(sd->screen, sd->menu, MENU_RECT_NBR,
					SDL_MapRGB(sd->s->format, 39, 40, 34));
	if (button_id == 35 || (sd->id_sel_par != 0 && sd->id_sel_obj != -1))
	{
		if (sd->id_sel_par != 0)
		{
			button_id = ft_define_sel_param(-1, sd->id_sel_par - 1);
			if (!(button_id >= 13 && button_id <= 15))
				ft_color_main_par_button(button_id, sd);
		}
		SDL_FillRect(sd->screen, &sd->menu[button_id],
					SDL_MapRGB(sd->s->format, 89, 90, 84));
	}
	if (sd->effect != 0)
		SDL_FillRect(sd->screen, &sd->menu[sd->effect],
					SDL_MapRGB(sd->s->format, 89, 90, 84));
	ft_add_text(sd);
}
