/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 08:53:09 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 08:53:10 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_obj_file(char *s, int i, t_sdl *sd)
{
	int			fd;
	char		*path;
	char		*end;
	t_obj		*ob;

	ob = NULL;
	path = ft_strstr(s, "<path>") + 6;
	end = ft_strstr(s, "</path>");
	path = ft_strsub(path, 0, end - path);
	if (!ft_strstr(path, ".obj") && free_it(NULL, NULL, path))
		return ;
	fd = open(path, O_RDWR);
	if (sd->obj_obj == NULL)
	{
		if (fd >= 0)
		{
			read_obj_file(fd, sd, s);
			ob = sd->obj_obj;
		}
	}
	if (path)
		ft_strdel(&path);
	close(fd);
	(ob) ? (sd->obj_obj[0].count = i) : 0;
}
