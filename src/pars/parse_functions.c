/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 10:58:29 by vmartynu          #+#    #+#             */
/*   Updated: 2018/06/12 17:14:48 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		chk_vector(cl_float3 in)
{
	cl_float3	ret;

	ret = in;
	(in.x < 0) ? (ret.x = 0) : 0;
	(in.x > 1) ? (ret.x = 1) : 0;
	(in.y < 0) ? (ret.y = 0) : 0;
	(in.y > 1) ? (ret.y = 1) : 0;
	(in.z < 0) ? (ret.z = 0) : 0;
	(in.z > 1) ? (ret.z = 1) : 0;
	return (ret);
}

cl_float3		get_vector(char *index, char *x, char *y, char *z)
{
	cl_float3	ret;

	ret = (cl_float3){{0, 0, 0}};
	if (index == ft_strstr(index, x))
		ret.x = ft_atof(index + 3);
	if (!(index = ft_strstr(index, y)))
		return (ret);
	if (index)
		ret.y = ft_atof(index + 3);
	index = ft_strstr(index, z);
	if (index)
		ret.z = ft_atof(index + 3);
	return (ret);
}

cl_float3		parse_cut_dir(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<cut_dir>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</cut_dir>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}

cl_float3		parse_cut_shift(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<cut_shift>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</cut_shift>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}

cl_float3		parse_pos(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<position>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</position>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}
