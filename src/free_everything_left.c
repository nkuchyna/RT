/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:19:59 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 16:20:01 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		delete(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		ft_strdel(&s[i]);
		i++;
	}
	free(s);
}

void			free_everything_left(t_sdl *sd)
{
	free(sd->menu);
	free(sd->places);
	SDL_FreeSurface(sd->s);
	TTF_CloseFont(sd->font);
	ft_free_text_surf(sd->texts);
	if (sd->obj)
		free(sd->obj);
	if (sd->obj_obj)
		free(sd->obj_obj);
	if (sd->light)
		free(sd->light);
	SDL_FreeSurface(sd->texture1);
	SDL_FreeSurface(sd->texture2);
	SDL_FreeSurface(sd->texture3);
	SDL_FreeSurface(sd->texture4);
	if (sd->textures)
		delete(sd->textures);
	if (sd->bump)
		delete(sd->bump);
	free(sd->color);
}

void			free_everything_left2(t_sdl *sd)
{
	ft_putendl("Error! Do not delete the default textures, they are needed \
for a kernel!");
	SDL_FreeSurface(sd->s);
	if (sd->obj)
		free(sd->obj);
	if (sd->obj_obj)
		free(sd->obj_obj);
	if (sd->light)
		free(sd->light);
	SDL_FreeSurface(sd->texture1);
	SDL_FreeSurface(sd->texture2);
	SDL_FreeSurface(sd->texture3);
	SDL_FreeSurface(sd->texture4);
	if (sd->textures)
		delete(sd->textures);
	if (sd->bump)
		delete(sd->bump);
}
