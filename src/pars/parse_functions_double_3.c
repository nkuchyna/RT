/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_double_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:22:55 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 14:22:56 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		parse_a(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<a>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 3)) : 0;
	return (ret);
}

float		parse_b(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<b>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 3)) : 0;
	return (ret);
}

float		parse_c(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<c>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 3)) : 0;
	return (ret);
}

float		parse_height(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<height>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 8)) : 0;
	return (ret);
}

float		parse_angle(char *obj)
{
	float	ret;
	char	*index;

	ret = 0;
	index = ft_strstr(obj, "<angle>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 7)) : 0;
	if (ret < M_PI)
		ret = tan(ret / 2);
	else
		ret = 0;
	return (ret);
}
