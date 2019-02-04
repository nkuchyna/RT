/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:35:15 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/16 12:43:31 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	cl_float3	*tri_v(t_o *o, int *f, char *s)
{
	cl_float3		*ret;

	ret = NULL;
	if (s)
	{
		ret = (cl_float3 *)ft_memalloc(sizeof(cl_float3) * 3);
		ret[0] = o->v[f[1] - 1];
		ret[1] = o->v[f[2] - 1];
		ret[2] = o->v[f[3] - 1];
	}
	return (ret);
}

static void			make_polygons(t_sdl *sd, t_o o, char *s, int i)
{
	cl_float3		*trivec;
	cl_float3		*popr;

	popr = NULL;
	while (i < o.c[3])
	{
		if (o.f[i][0] == 3)
		{
			trivec = tri_v(&o, o.f[i], s);
			init_triangle(&sd->obj_obj[i], trivec, s);
			free(trivec);
		}
		i++;
	}
}

static void			parse_object_string(char *scene, t_sdl *sd, int *i, char *s)
{
	t_o				o;
	t_obj			*ret;
	int				j;

	if (i[0] < 3 && i[2] <= 1)
		return ;
	ret = NULL;
	sd->count = i[2];
	j = 0;
	o = get_obj_data(scene, i);
	ret = get_sphere(i[0], &o);
	sd->obj_obj = ft_memalloc(sizeof(t_obj) * o.c[3]);
	if (ret)
		sd->obj_obj[j++] = *ret;
	(o.c[3] > 0) ? make_polygons(sd, o, s, j) : 0;
	j = 0;
	if (o.fl > 0)
		while (j < o.c[3])
			free(o.f[j++]);
	free(o.f);
	free(o.sharp);
	free(o.vn);
	free(o.v);
	free(o.vt);
	free(ret);
}

void				read_obj_file(int fd, t_sdl *sd, char *s)
{
	int				ar[5];
	char			*temp;
	char			*scene;
	char			*line;

	scene = ft_strdup("");
	line = NULL;
	init_int_array(ar, 5, 0);
	while (get_next_line(fd, &line))
	{
		if (line)
		{
			(line[0] == 'v') ? ((ar[0])++) : 0;
			(line[0] == '#') ? ((ar[1])++) : 0;
			(line[0] == 'f') ? ((ar[2])++) : 0;
			(!ft_strncmp(line, "vn", 2)) ? (ar[3])++ : 0;
			(!ft_strncmp(line, "vt", 2)) ? (ar[4])++ : 0;
			temp = ft_strjoin(scene, line);
			free_it(line, scene, NULL);
			scene = ft_strjoin(temp, "\n");
			ft_strdel(&temp);
		}
	}
	(ar[0] > 3 && ar[2] >= 1) ? parse_object_string(scene, sd, ar, s) : 0;
	free(scene);
}
