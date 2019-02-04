/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:32:01 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 10:32:03 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			ft_vector_len(cl_float3 vec)
{
	float		result;

	result = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (result);
}

cl_float3		ft_normalize(cl_float3 vec)
{
	cl_float3	result;
	float		vec_len;

	if (vec.x == 0 && vec.y == 0 && vec.z == 0)
		return (vec);
	vec_len = ft_vector_len(vec);
	result.x = vec.x / vec_len;
	result.y = vec.y / vec_len;
	result.z = vec.z / vec_len;
	return (result);
}

cl_float3		ft_cross(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3 result;

	result.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	result.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	result.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (result);
}

int				ft_vector_compare(cl_float3 a, cl_float3 b)
{
	if ((a.x == b.x && a.y == b.y && a.z == b.z)
	|| (a.x == -b.x && a.y == -b.y && a.z == -b.z))
		return (1);
	return (0);
}
