/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 10:00:31 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 10:46:41 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			f_remalloc(t_sdl *sd)
{
	int				i;
	int				j;
	t_obj			*objects;

	j = -1;
	if (sd->obj)
	{
		if (sd->obj[0].count > 0)
			i = sd->obj[0].count - sd->count;
		else
		{
			i = sd->count;
			sd->obj[0].count = sd->count;
		}
		objects = ft_memalloc(sizeof(t_obj) * sd->obj[0].count);
		while (++j < i)
			objects[j] = sd->obj[j];
		i = 0;
		while (i < sd->count)
			objects[j++] = sd->obj_obj[i++];
		free(sd->obj);
		sd->obj = objects;
	}
}

void				read_fd(int fd)
{
	t_sdl			sd;
	int				z;

	SDL_Init(SDL_INIT_EVERYTHING);
	init_ttf(&sd);
	init_sdl(&sd);
	z = read_scene_from_file(fd, &sd);
	if (z < 0 || sd.count < 0)
	{
		ft_putendl("Error: WRONG SCENE!!!!!!!");
		exit(1);
	}
	if (z == 0)
		upload_textures_and_bump(&sd);
	if (sd.count > 0 && z >= 0)
		f_remalloc(&sd);
	ft_create_menu(&sd);
	if (!sd.texture1 || !sd.texture2 || !sd.texture3 || !sd.texture4)
	{
		free_everything_left(&sd);
		exit(1);
	}
	if (z == 0 && sd.count > -1)
		loop(&sd);
	free_everything_left(&sd);
}

int					main(int argc, char **argv)
{
	int				fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDWR);
		if (fd >= 0)
			read_fd(fd);
		else
		{
			ft_putstr(argv[1]);
			ft_putstr(": ");
			ft_putstr(strerror(errno));
			ft_putchar('\n');
		}
	}
	else
		ft_putstr("usage: RT (filename)\n");
	return (0);
}
