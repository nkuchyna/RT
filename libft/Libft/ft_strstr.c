/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:15:47 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 17:49:23 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	size_t	j;
	char	*b;
	int		c;

	b = (char *)big;
	i = 0;
	c = 0;
	if (little[0] == '\0')
		return (b + i);
	while (b[i] != '\0')
	{
		j = i;
		c = 0;
		while (b[j] == little[c])
		{
			j++;
			c++;
			if (little[c] == '\0')
				return (b + i);
		}
		i++;
	}
	return (NULL);
}
