/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 11:54:08 by vmartynu          #+#    #+#             */
/*   Updated: 2017/10/28 12:48:17 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destptr, const char *srcptr, size_t num)
{
	size_t i;

	i = 0;
	while (num > 0 && srcptr[i] != '\0')
	{
		destptr[i] = srcptr[i];
		num--;
		i++;
	}
	while (num > 0)
	{
		destptr[i] = '\0';
		i++;
		num--;
	}
	return (destptr);
}
