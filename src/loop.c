/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:16:52 by vmartynu          #+#    #+#             */
/*   Updated: 2018/05/30 16:22:08 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_t_loop(t_loop *l, t_sdl *sd)
{
	l->dir_old = sd->cam.dir;
	l->angle.x = 0;
	l->angle.y = 0;
	l->angle.z = 0;
	l->ss = 0;
	sd->is_running = 1;
	l->i = 0;
	l->n = HEIGHT * WIDTH;
	l->tmp = 0;
	l->b = 0;
	l->keyboardstate = SDL_GetKeyboardState(NULL);
}

static void		poll_event(t_loop *l, t_sdl *sd)
{
	if (sd->event.type == SDL_QUIT)
		sd->is_running = 0;
	if (sd->event.type == SDL_KEYDOWN && sd->event.key.keysym.sym ==
		SDLK_ESCAPE)
		sd->is_running = 0;
	if (sd->event.type == SDL_MOUSEBUTTONDOWN)
		sdl_mouse_button_down(sd, l);
	if (sd->event.type == SDL_MOUSEBUTTONUP)
		l->b = 0;
	if (l->b && sd->event.type == SDL_MOUSEMOTION)
		sdl_mouse_motion(sd, l);
	if (l->keyboardstate[SDL_SCANCODE_UP])
		sdl_scan_code_up(sd, l);
	if (l->keyboardstate[SDL_SCANCODE_DOWN])
		sdl_scan_code_down(sd, l);
	if (l->keyboardstate[SDL_SCANCODE_S] || sd->id_sel_rect == 35)
		sdl_scan_code_s(sd, l);
}

static void		count_samps(t_sdl *sd, t_loop *l)
{
	init_buffs(sd, l->n, l->i);
	SDL_FreeSurface(sd->texts[34]);
	if (l->i < 10000)
	{
		l->text_str = ft_change_text_str(l->i);
		sd->texts[34] = TTF_RenderText_Solid(sd->font,
		l->text_str, sd->t_color);
	}
	render(sd, l->i);
	ft_strdel(&l->text_str);
	l->i++;
}

static void		release_cl_mem(t_sdl *sd)
{
	clReleaseMemObject(sd->objc);
	clReleaseMemObject(sd->lightc);
	clReleaseMemObject(sd->screenc);
	clReleaseProgram(sd->program);
	clReleaseKernel(sd->kernel);
	clReleaseCommandQueue(sd->commands);
	clReleaseContext(sd->context);
	SDL_DestroyWindow(sd->window);
}

void			loop(t_sdl *sd)
{
	t_loop		l;

	init_t_loop(&l, sd);
	init_cl(sd);
	cl_enqueue_image(sd);
	srand(time(NULL));
	sd->err = clGetKernelWorkGroupInfo(sd->kernel, sd->device_id,
	CL_KERNEL_WORK_GROUP_SIZE, sizeof(sd->local), &sd->local, NULL);
	(sd->err != CL_SUCCESS) ? (error(10, sd)) : 0;
	sd->global = ceil(l.n / (float)sd->local) * sd->local;
	sd->color = (cl_float3*)malloc(sizeof(cl_float3) * WIDTH * HEIGHT);
	while (sd->is_running)
	{
		if (SDL_PollEvent(&sd->event))
			poll_event(&l, sd);
		l.text_str = NULL;
		if (l.i < SAMPS)
			count_samps(sd, &l);
	}
	release_cl_mem(sd);
}
