/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 09:59:36 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 09:59:39 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		parse_c1(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<c1>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</c1>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}

cl_float3		parse_c2(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<c2>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</c2>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}

cl_float3		parse_c3(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<c3>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</c3>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}

cl_float3		parse_pos_light(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<position>");
	if (index - ft_strstr(obj, "</light>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<x>")) ||
		!(check = ft_strstr(index, "</position>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<x>", "<y>", "<z>");
	return (ret);
}

cl_float3		parse_dir_light(char *obj)
{
	cl_float3	ret;
	char		*index;

	ret = (cl_float3){{0, 0, 0}};
	index = ft_strstr(obj, "<direction>");
	if (index - ft_strstr(obj, "</light>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	index = ft_strstr(index, "<x>");
	if (index)
		ret.x = ft_atof(index + 3);
	else
		(ret.x = 0.0);
	index = ft_strstr(index, "<y>");
	if (index)
		(ret.y = ft_atof(index + 3));
	else
		(ret.y = 1);
	index = ft_strstr(index, "<z>");
	if (index)
		(ret.z = ft_atof(index + 3));
	else
		(ret.z = 0.0);
	return (ret);
}
