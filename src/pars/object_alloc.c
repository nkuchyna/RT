/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 10:14:55 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/03 10:15:08 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		ft_check_unick(char *source, int k, char **text, int *count)
{
	int				i;
	int				ret;
	SDL_Surface		*surf_text;

	i = 0;
	ret = 1;
	if (!(surf_text = SDL_LoadBMP(source)))
		return (0);
	while (i < k)
	{
		if (ft_strcmp(text[i], source) == 0)
		{
			ret = 0;
			(*count)--;
			break ;
		}
		i++;
	}
	SDL_FreeSurface(surf_text);
	return (ret);
}

static char		**read_text(char *s, int *k, char *t_beg, char *t_end)
{
	int		i;
	char	**text;
	char	*sub;

	text = (char**)malloc(sizeof(char*) * *k + 1);
	i = 0;
	while (i < *k && s)
	{
		s = ft_strstr(s, t_beg);
		if (s && ft_strstr(s, t_end) && (ft_strstr(s, t_end) - s) > 0)
		{
			if (ft_check_unick((sub = ft_strsub(s, ft_strlen(t_beg),
			ft_strstr(s, t_end) - s - ft_strlen(t_beg))), i, text, &(*k)) == 1)
				text[i++] = ft_strdup(sub);
		}
		else
		{
			(*k)--;
			continue;
		}
		s = ft_strstr(s, t_end);
		ft_strdel(&sub);
	}
	text[i] = NULL;
	return (text);
}

void			object_alloc(char *scene, t_sdl *sd, int *count)
{
	int			i;
	char		**text;
	char		**bump;

	i = -1;
	text = read_text(scene, &count[2], "<texture>", "</texture>");
	bump = read_text(scene, &count[3], "<bump>", "</bump>");
	sd->textures = text;
	sd->bump = bump;
	sd->obj = ft_memalloc(sizeof(t_obj) * count[0] + 1);
	parse_scene_objects(sd, scene, count[0], i);
}
