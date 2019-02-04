/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:38:39 by vmartynu          #+#    #+#             */
/*   Updated: 2018/05/30 16:10:00 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_sdl(t_sdl *sd)
{
	sd->neg = 0;
	sd->gpu = 1;
	sd->count = 0;
	sd->texture1 = NULL;
	sd->texture2 = NULL;
	sd->texture3 = NULL;
	sd->texture4 = NULL;
	sd->bump = NULL;
	sd->textures = NULL;
	sd->obj = NULL;
	sd->obj_obj = NULL;
	sd->light = NULL;
	sd->is_running = 1;
	sd->effect = 4;
	sd->id_sel_obj = -1;
	sd->window = SDL_CreateWindow("RT",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	WIDTH, HEIGHT + MENU_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	sd->screen = SDL_GetWindowSurface(sd->window);
	SDL_memset(sd->screen->pixels, 0, sd->screen->h * sd->screen->pitch);
}

void	init_ttf(t_sdl *sd)
{
	if (TTF_Init() < 0)
		ft_putendl("Error: TTF library was not initialized!");
	if ((sd->font = TTF_OpenFont("fonts/OpenSans.ttf", 15)) == NULL)
	{
		ft_putendl("Error: There is not such font!");
		exit(1);
	}
	sd->t_color.r = 200;
	sd->t_color.g = 200;
	sd->t_color.b = 200;
}
