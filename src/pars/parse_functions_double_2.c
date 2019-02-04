/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_double_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:21:41 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 14:21:42 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			parse_cut(char *obj)
{
	char	*string;
	int		ret;
	char	*b;
	char	*e;
	char	*end_obj;

	end_obj = ft_strstr(obj, "</object>");
	ret = 0;
	string = NULL;
	b = ft_strstr(obj, "<cut>");
	e = ft_strstr(obj, "</cut>");
	if (end_obj - e < 0)
		return (0);
	if (b && e)
		string = ft_strsub(b, 5, e - (b + 5));
	else
		return (0);
	(!ft_strncmp(string, "+x", 2)) ? ret = PLUS_X : 0;
	(!ft_strncmp(string, "-x", 2)) ? ret = MINUS_X : 0;
	(!ft_strncmp(string, "+y", 2)) ? ret = PLUS_Y : 0;
	(!ft_strncmp(string, "-y", 2)) ? ret = MINUS_Y : 0;
	(!ft_strncmp(string, "+z", 2)) ? ret = PLUS_Z : 0;
	(!ft_strncmp(string, "-z", 2)) ? ret = MINUS_Z : 0;
	free(string);
	return (ret);
}

int			parse_material(char *obj)
{
	int		ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<material>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index)
	{
		if (!ft_strncmp(index + 10, "diffuse", 7))
			ret = 0;
		else if (!ft_strncmp(index + 10, "mirror", 6))
			ret = 1;
		else if (!ft_strncmp(index + 10, "glossy", 6))
			ret = 2;
		else if (!ft_strncmp(index + 10, "transparency", 12))
			ret = 4;
		else if (!ft_strncmp(index + 10, "dif+mir", 7))
			ret = 3;
		else if (!ft_strncmp(index + 10, "dif+transp", 10))
			ret = 5;
	}
	return (ret);
}

float		parse_radius(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<radius>");
	(index) ? (ret = ft_atof(index + 8)) : 0;
	return (ret);
}

float		parse_phi(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<phi>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 5)) : 0;
	return (ret);
}

float		parse_s_radius(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<s_radius>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 10)) : 0;
	return (ret);
}
