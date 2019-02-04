/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 09:17:03 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/15 09:17:04 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_in_light(char **s)
{
	char		*start;
	char		*end;

	start = ft_strstr(*s, "<light>");
	end = ft_strstr(*s, "</light>");
	if (start && end)
		return (0);
	return (1);
}

static int		check_in_camera(char **s)
{
	char		*start;
	char		*end;

	start = ft_strstr(*s, "<camera>");
	end = ft_strstr(*s, "</camera>");
	if (start && end)
		return (0);
	return (1);
}

static int		check_in_object(char **s)
{
	char		*start;
	char		*end;

	start = ft_strstr(*s, "<object >");
	end = ft_strstr(*s, "</object>");
	if (start && end)
		return (0);
	return (1);
}

int				check_in(char **s)
{
	if (!ft_strncmp(*s, "<object", 7))
	{
		if (check_in_light(s) == 0)
			return (0);
		if (check_in_camera(s) == 0)
			return (0);
	}
	else if (!ft_strncmp(*s, "<light>", 7))
	{
		if (check_in_object(s) == 0)
			return (0);
		if (check_in_camera(s) == 0)
			return (0);
	}
	else if (!ft_strncmp(*s, "<camera>", 8))
	{
		if (check_in_light(s) == 0)
			return (0);
		if (check_in_object(s) == 0)
			return (0);
	}
	return (1);
}
