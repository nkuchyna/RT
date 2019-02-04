/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_double_4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:24:05 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 14:24:07 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		parse_refract(char *obj)
{
	float	ret;
	char	*index;

	ret = 1.5;
	index = ft_strstr(obj, "<refraction>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 12)) : 0;
	return (ret);
}

float		parse_diffuse(char *obj)
{
	float	ret;
	char	*index;

	ret = 0.5;
	index = ft_strstr(obj, "<diffuse>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 9)) : 0;
	ret = ret < 0 ? 0 : ret;
	ret = ret > 1 ? 1 : ret;
	return (ret);
}

float		parse_cos_pow(char *obj)
{
	float	ret;
	char	*index;

	ret = 1;
	index = ft_strstr(obj, "<cos_pow>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 9)) : 0;
	ret = ret < 1 ? 1 : ret;
	return (ret);
}

float		parse_ambient(char *obj)
{
	float	ret;
	char	*index;

	ret = 0.01;
	index = ft_strstr(obj, "<ambient>");
	if (index == NULL)
		return (ret);
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	(index) ? (ret = ft_atof(index + 9)) : 0;
	ret = ret < 0 ? 0 : ret;
	ret = ret > 1 ? 1 : ret;
	return (ret);
}

float		parse_pattern(char *obj)
{
	char	*begin;
	char	*end;

	begin = ft_strstr(obj, "<pattern>");
	end = ft_strstr(obj, "</pattern>");
	if (!begin || !end || !((end - begin) > 0) ||
		!((ft_strstr(obj, "</object>") - end) > 0))
		return (-1);
	return (ft_atof(begin + 9));
}
