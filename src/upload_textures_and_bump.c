/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_textures_and_bump.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 20:41:48 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/26 20:42:04 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			load_default_bmp(t_sdl *sd)
{
	if (sd->texture1 == NULL)
		sd->texture1 = SDL_LoadBMP("./textures/tile3.bmp");
	if (sd->texture2 == NULL)
		sd->texture2 = SDL_LoadBMP("./textures/tile3.bmp");
	if (sd->texture3 == NULL)
		sd->texture3 = SDL_LoadBMP("./textures/tile3.bmp");
	if (sd->texture4 == NULL)
		sd->texture4 = SDL_LoadBMP("./textures/tile3.bmp");
	if (!sd->texture1 || !sd->texture2 || !sd->texture3 || !sd->texture4)
		return (-1);
	return (0);
}

void				ft_load_textures(t_sdl *sd, int size)
{
	if (size <= 4)
	{
		if (sd->textures && sd->textures[0])
			sd->texture1 = SDL_LoadBMP(sd->textures[0]);
		else
			return ;
		if (sd->textures && sd->textures[1])
			sd->texture2 = SDL_LoadBMP(sd->textures[1]);
		else
			return ;
	}
	if (size == 4)
	{
		if (sd->textures && sd->textures[2])
			sd->texture3 = SDL_LoadBMP(sd->textures[2]);
		else
			return ;
		if (sd->textures && sd->textures[3])
			sd->texture4 = SDL_LoadBMP(sd->textures[3]);
		else
			return ;
	}
}

void				ft_load_bump(t_sdl *sd, int size)
{
	if (size <= 4)
	{
		if (sd->bump && sd->bump[0] != NULL)
			sd->texture3 = SDL_LoadBMP(sd->bump[0]);
		else
			return ;
		if (sd->bump && sd->bump[1] != NULL)
			sd->texture4 = SDL_LoadBMP(sd->bump[1]);
		else
			return ;
	}
	if (size == 4)
	{
		if (sd->bump && sd->bump[2] != NULL)
			sd->texture1 = SDL_LoadBMP(sd->bump[2]);
		else
			return ;
		if (sd->bump && sd->bump[3] != NULL)
			sd->texture2 = SDL_LoadBMP(sd->bump[3]);
		else
			return ;
	}
}

void				upload_textures_and_bump(t_sdl *sd)
{
	if (sd->textures[0] == NULL && sd->bump[0] == NULL)
		load_default_bmp(sd);
	if (sd->bump[0] == NULL && sd->textures[0] != NULL)
		ft_load_textures(sd, 4);
	if (sd->textures[0] == NULL && sd->bump[0] != NULL)
		ft_load_bump(sd, 4);
	if (sd->textures[0] != NULL && sd->bump[0] != NULL)
	{
		ft_load_textures(sd, 2);
		ft_load_bump(sd, 2);
	}
	if (load_default_bmp(sd) == -1)
	{
		free_everything_left2(sd);
		exit(1);
	}
	SDL_LockSurface(sd->texture1);
	SDL_LockSurface(sd->texture2);
	SDL_LockSurface(sd->texture3);
	SDL_LockSurface(sd->texture4);
}
