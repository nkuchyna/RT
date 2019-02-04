/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_float.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:22:24 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/06/07 18:48:16 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_def_texture_nbr(char **textures, char *sub)
{
	int			i;

	i = 0;
	while (textures[i] != NULL)
	{
		if (ft_strcmp(textures[i], sub) == 0)
			return (i + 1);
		i++;
	}
	return (-1);
}

int			ft_define_text(char **textures, char *obj, char *t_beg, char *t_end)
{
	char	*begin;
	char	*end;
	char	*sub;
	int		texture_nbr;
	int		t_beg_len;

	if (!t_beg || !t_end)
		return (-1);
	texture_nbr = -1;
	begin = ft_strstr(obj, t_beg);
	end = ft_strstr(obj, t_end);
	if (!begin || !end || !((end - begin) > 0) || !((ft_strstr(obj,
		"</object>") - end) > 0))
		return (-1);
	t_beg_len = ft_strlen(t_beg);
	if (begin != 0)
	{
		sub = ft_strsub(begin, t_beg_len, end - begin - t_beg_len);
		texture_nbr = ft_def_texture_nbr(textures, sub);
		ft_strdel(&sub);
	}
	return (texture_nbr);
}

float		parse_phi_light(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<phi>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</light>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 5)) : 0;
	return (ret);
}

float		parse_negative(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<negative>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atoi(index + 10)) : 0;
	return (ret);
}
