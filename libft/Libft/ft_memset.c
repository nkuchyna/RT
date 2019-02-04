/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:59:17 by vmartynu          #+#    #+#             */
/*   Updated: 2017/10/28 16:09:16 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	size_t			i;
	unsigned char	*mempt;
	unsigned char	*temp;

	mempt = (unsigned char *)memptr;
	temp = mempt;
	i = 0;
	while (i++ < num)
		*(mempt++) = (unsigned char)val;
	return (temp);
}
