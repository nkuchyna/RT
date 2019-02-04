/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 09:50:13 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/06 09:50:15 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		parse_m_blur(char *obj)
{
	cl_float3	ret;
	char		*index;

	ret = (cl_float3){{0, 0, 0}};
	index = ft_strstr(obj, "<m_blur>");
	if (index - ft_strstr(obj, "</object>") > 0)
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

cl_float3		parse_dir(char *obj)
{
	cl_float3	ret;
	char		*index;

	ret = (cl_float3){{0, 0, 0}};
	index = ft_strstr(obj, "<direction>");
	if (index - ft_strstr(obj, "</object>") > 0)
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

cl_float3		parse_color(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0.6, 0.6, 0.6}};
	index = ft_strstr(obj, "<color>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<r>")) ||
		!(check = ft_strstr(index, "</color>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<r>", "<g>", "<b>");
	ret = chk_vector(ret);
	return (ret);
}

cl_float3		parse_color_light(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0.6, 0.6, 0.6}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<color>");
	if (index - ft_strstr(obj, "</light>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<r>")) ||
		!(check = ft_strstr(index, "</color>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<r>", "<g>", "<b>");
	return (ret);
}

cl_float3		parse_emission(char *obj)
{
	cl_float3	ret;
	char		*index;
	char		*check;

	ret = (cl_float3){{0, 0, 0}};
	ret.x = 0.0f;
	ret.y = 0.0f;
	ret.z = 0.0f;
	index = ft_strstr(obj, "<emission>");
	if (index - ft_strstr(obj, "</object>") > 0)
		return (ret);
	if (index == NULL)
		return (ret);
	if (!(index = ft_strstr(index, "<r>")) ||
		!(check = ft_strstr(index, "</emission>")) || (index - check > 0))
		return (ret);
	ret = get_vector(index, "<r>", "<g>", "<b>");
	(ret.x < 0) ? (ret.x = 0) : 0;
	(ret.y < 0) ? (ret.y = 0) : 0;
	(ret.z < 0) ? (ret.z = 0) : 0;
	return (ret);
}
