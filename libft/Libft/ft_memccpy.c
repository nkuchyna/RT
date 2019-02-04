/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:39:42 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 17:52:58 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i++ < n)
	{
		*(unsigned char *)dest = *(unsigned char *)(src++);
		if (*(unsigned char*)(dest++) == (unsigned char)c)
			return (dest);
	}
	return (NULL);
}
