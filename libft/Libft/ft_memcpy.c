/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:43:03 by vmartynu          #+#    #+#             */
/*   Updated: 2017/10/31 12:47:48 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dests;
	unsigned char	*srcs;

	dests = (unsigned char *)dest;
	srcs = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dests[i] = srcs[i];
		i++;
	}
	return (dests);
}
