/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions_double_5.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:04:06 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/19 18:04:58 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		parse_text_scale(char *obj)
{
	float	ret;
	char	*index;

	ret = 1;
	index = ft_strstr(obj, "<text_scale>");
	(index) ? (ret = 1 / ft_atof(index + 12)) : 0;
	if (ret > 10 || ret < 0)
		ret = 1;
	return (ret);
}
