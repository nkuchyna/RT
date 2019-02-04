/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_color_effect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:24:42 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/07/28 18:25:18 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_float3	ft_sepia_tone(cl_float3 color)
{
	cl_float3	result;

	result.x = (color.x * 0.393) + (color.y * 0.769) + (color.z * 0.189);
	result.y = (color.x * 0.349) + (color.y * 0.686) + (color.z * 0.168);
	result.z = (color.x * 0.272) + (color.y * 0.534) + (color.z * 0.131);
	return (result);
}

static cl_float3	ft_black_white_tone(cl_float3 color)
{
	float		s_color;
	cl_float3	new_color;

	s_color = color.x * 0.299 + color.y * 0.587 + color.z * 0.114;
	new_color.x = s_color;
	new_color.y = s_color;
	new_color.z = s_color;
	return (new_color);
}

static cl_float3	ft_negative_tone(cl_float3 color)
{
	cl_float3	new_color;

	new_color.x = 0.01 - color.x;
	new_color.y = 0.01 - color.y;
	new_color.z = 0.01 - color.z;
	return (new_color);
}

cl_float3			ft_add_color_effect(int effect, cl_float3 color)
{
	if (effect == 1)
		color = ft_sepia_tone(color);
	if (effect == 2)
		color = ft_black_white_tone(color);
	if (effect == 3)
		color = ft_negative_tone(color);
	return (color);
}
