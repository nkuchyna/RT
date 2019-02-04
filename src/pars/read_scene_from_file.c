/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 08:30:41 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 12:54:08 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_camera(t_sdl *sd, char *scene)
{
	char *begin;
	char *end;
	char *s_cam;

	s_cam = NULL;
	begin = ft_strstr(scene, "<camera>");
	end = ft_strstr(scene, "</camera>");
	sd->cam.pos = (cl_float3){{0, 0, 800}};
	sd->cam.dir = (cl_float3){{0, 0, -1}};
	sd->cam.dir = ft_normalize(sd->cam.dir);
	if (end && begin)
	{
		s_cam = ft_strsub(begin, 0, end + 9 - begin);
		if (check_in(&s_cam))
		{
			sd->cam.pos = parse_pos(begin);
			sd->cam.dir = parse_dir(begin);
			sd->cam.dir = ft_normalize(sd->cam.dir);
		}
		free(s_cam);
	}
}

static void		light_alloc(char *scene, t_sdl *sd, int count)
{
	sd->light = ft_memalloc(sizeof(t_light) * (count + 1));
	sd->light[0].n = count + 1;
	if (count > 0)
		parse_scene_lights(sd, scene, count);
	else if (count == 0)
		sd->light[0].id = 777;
}

static int		parse_scene_xml(char *scene, t_sdl *sd)
{
	char		*begin;
	char		*end;
	char		*sub;
	int			i;
	int			count[4];

	init_int_array(count, 4, 0);
	i = -1;
	sd->light = NULL;
	begin = ft_strstr(scene, "<scene>");
	end = ft_strstr(scene, "</scene>");
	get_camera(sd, scene);
	if (begin && end && (begin = begin + 7))
	{
		sub = ft_strsub(scene, 7, end - begin);
		i = chk_tg(sub, count, NULL, 1);
		sd->ambient = parse_ambient(scene);
		if (i == 0 && count[0] > 0)
			object_alloc(scene, sd, count);
		else if (sd->count == 0)
			sd->count = -1;
		(i == 0 && count[1] >= 0) ? light_alloc(scene, sd, count[1]) : 0;
	}
	return (i);
}

int				read_scene_from_file(int fd, t_sdl *sd)
{
	char		*line;
	char		*scene;
	char		*temp;
	int			i;

	i = -12;
	line = NULL;
	scene = ft_strdup("");
	get_next_line(fd, &line);
	(line && !ft_strncmp(line, "<?xml?>", 7)) ? i = 1 : 0;
	ft_strdel(&line);
	if (i == 1)
	{
		while (get_next_line(fd, &line))
		{
			temp = ft_strjoin(scene, line);
			ft_strdel(&line);
			ft_strdel(&scene);
			scene = ft_strjoin(temp, "\n");
			ft_strdel(&temp);
		}
		i = parse_scene_xml(scene, sd);
	}
	ft_strdel(&scene);
	return (i);
}
