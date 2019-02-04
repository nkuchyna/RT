/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:32:06 by vmartynu          #+#    #+#             */
/*   Updated: 2018/08/08 10:32:07 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		ft_vector_mult(cl_float3 vec, float num)
{
	cl_float3 result;

	result.x = vec.x * num;
	result.y = vec.y * num;
	result.z = vec.z * num;
	return (result);
}

cl_float3		ft_vector_div(cl_float3 vec, float num)
{
	cl_float3 result;

	result.x = vec.x;
	result.y = vec.y;
	result.z = vec.z;
	if (num != 0.0)
	{
		result.x = vec.x / num;
		result.y = vec.y / num;
		result.z = vec.z / num;
	}
	return (result);
}

float			ft_vector_dot(cl_float3 vec1, cl_float3 vec2)
{
	float result;

	result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (result);
}

cl_float3		ft_vector_sub(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3 result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

cl_float3		ft_vector_add(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3 result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}
