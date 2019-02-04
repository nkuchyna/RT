/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:20:53 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 17:57:29 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*snew;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		snew = (char *)malloc(sizeof(char) * i + 1);
		i = 0;
		if (snew)
		{
			while (s[i])
			{
				snew[i] = f(s[i]);
				i++;
			}
			snew[i] = '\0';
			return (snew);
		}
		else
			return (NULL);
	}
	else
		return (NULL);
}
