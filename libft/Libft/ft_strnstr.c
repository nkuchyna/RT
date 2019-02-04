/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:16:39 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/15 15:14:39 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t		i;
	size_t		j;
	char		*b;
	size_t		c;

	b = (char *)big;
	i = 0;
	if (big == little || little[0] == '\0')
		return (b + i);
	if (n - 1 == ft_strlen(big))
		return (ft_strstr(big, little));
	while (b[i] != '\0' && n--)
	{
		j = i;
		c = 0;
		while (b[j] == little[c] && c <= n && b[j] != '\0')
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
