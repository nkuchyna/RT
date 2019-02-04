/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 20:34:43 by vmartynu          #+#    #+#             */
/*   Updated: 2018/06/16 14:03:48 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_spot(char *s, int i, t_sdl *sd)
{
	sd->light[i].id = 777;
	(check_in(&s)) ? sd->light[i].id = 2 : 0;
	sd->light[i].pos = parse_pos_light(s);
	sd->light[i].dir = ft_normalize(parse_dir_light(s));
	sd->light[i].color = parse_color_light(s);
	sd->light[i].phi = parse_phi_light(s);
}

void			parse_point(char *s, int i, t_sdl *sd)
{
	sd->light[i].id = 777;
	(check_in(&s)) ? sd->light[i].id = 1 : 0;
	sd->light[i].pos = parse_pos_light(s);
	sd->light[i].color = parse_color_light(s);
	sd->light[i].n = sd->light[0].n;
}

void			parse_directional(char *s, int i, t_sdl *sd)
{
	sd->light[i].id = 777;
	(check_in(&s)) ? sd->light[i].id = 0 : 0;
	sd->light[i].color = parse_color_light(s);
	sd->light[i].dir = ft_normalize(parse_dir_light(s));
	sd->light[i].n = sd->light[0].n;
}

static char		*get_light(char **index)
{
	char		*start;
	char		*tmp;
	char		*end;
	char		*sub;

	sub = NULL;
	tmp = NULL;
	start = ft_strstr(*index, "<light>");
	end = ft_strstr(start, "</light>");
	if (start && end)
	{
		sub = ft_strsub(start, 0, (end + 8) - start);
		tmp = ft_strstr(sub, "<type>");
		if (tmp)
			*index = ft_strstr(start, "<type>");
		else
			*index = end;
	}
	return (sub);
}

int				parse_scene_lights(t_sdl *sd, char *scene, int count)
{
	char		*index;
	char		*sub;
	int			i;
	int			ret;

	index = scene;
	i = 0;
	ret = 0;
	while (i < count && (sub = get_light(&index)))
	{
		if (!ft_strncmp(index, "<type>spot", 10))
			parse_spot(sub, i, sd);
		else if (!ft_strncmp(index, "<type>point", 11))
			parse_point(sub, i, sd);
		else if (!ft_strncmp(index, "<type>directional", 17))
			parse_directional(sub, i, sd);
		else if (count-- > -2)
		{
			free(sub);
			continue;
		}
		free(sub);
		i++;
	}
	return (0);
}
