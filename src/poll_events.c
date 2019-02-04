/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:20:21 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 15:20:23 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sdl_mouse_button_down(t_sdl *sd, t_loop *l)
{
	if (sd->event.button.clicks == 1)
	{
		SDL_GetMouseState(&l->x, &l->y);
		if (l->y > 512)
		{
			sd->id_sel_rect = ft_define_select_rect(l->x, l->y, sd->menu);
			if (l->select_flag == 1
			&& ft_def_change_par_buttom(sd->id_sel_rect, sd->id_sel_par) == 1)
				l->i = 0;
			ft_menu_button_action(sd, l->select_flag);
		}
		else
			l->b = 1;
	}
	if (sd->event.button.clicks == 2 && l->y < 512)
	{
		sd->id_sel_par = 0;
		l->select_flag = 1;
		sd->id_sel_obj = ft_choose_obj(sd, l->x, l->y);
	}
}

void	sdl_mouse_motion(t_sdl *sd, t_loop *l)
{
	if (l->b == 1)
		SDL_GetRelativeMouseState(&l->x, &l->y);
	l->angle = mousemot(sd->cam.dir);
	l->dir = sd->cam.dir;
	sd->cam.dir.y = l->dir.y * cos(l->angle.x) + l->dir.z * sin(l->angle.x);
	sd->cam.dir.z = -(l->dir.y) * sin(l->angle.x) + l->dir.z * cos(l->angle.x);
	l->dir = sd->cam.dir;
	sd->cam.dir.x = l->dir.x * cos(l->angle.y) + l->dir.z * sin(l->angle.y);
	sd->cam.dir.z = -(l->dir.x) * sin(l->angle.y) + l->dir.z * cos(l->angle.y);
	l->i = 0;
	init_buffs(sd, l->n, l->i);
	l->i++;
	l->b = -1;
}

void	sdl_scan_code_up(t_sdl *sd, t_loop *l)
{
	sd->cam.pos = ft_vector_add(sd->cam.pos, ft_vector_mult(sd->cam.dir, 10));
	l->i = 0;
	init_buffs(sd, l->n, l->i);
	l->i++;
}

void	sdl_scan_code_down(t_sdl *sd, t_loop *l)
{
	sd->cam.pos = ft_vector_add(sd->cam.pos, ft_vector_mult(sd->cam.dir, -10));
	l->i = 0;
	init_buffs(sd, l->n, l->i);
	l->i++;
}

void	sdl_scan_code_s(t_sdl *sd, t_loop *l)
{
	char		*number;
	char		*name;
	SDL_Surface	*tmp;
	SDL_Rect	r;

	r.w = WIDTH;
	r.h = HEIGHT;
	number = ft_itoa(l->ss);
	name = ft_strjoin(number, ".png");
	l->sshot = SDL_ConvertSurfaceFormat(sd->screen, SDL_PIXELFORMAT_RGB24, 0);
	tmp = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, l->sshot->format->\
		BitsPerPixel, l->sshot->format->Rmask, l->sshot->format->\
		Gmask, l->sshot->format->Bmask, l->sshot->format->Amask);
	SDL_BlitSurface(l->sshot, NULL, tmp, NULL);
	IMG_SavePNG(tmp, name);
	l->ss++;
	SDL_FreeSurface(l->sshot);
	SDL_FreeSurface(tmp);
	free(number);
	free(name);
	sd->id_sel_rect = -1;
}
