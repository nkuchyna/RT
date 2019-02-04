/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 11:05:51 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/03 17:06:32 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s_new;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		s_new = (char *)malloc(sizeof(char) * i + 1);
		i = 0;
		if (s_new)
		{
			while (s[i])
			{
				s_new[i] = f(i, s[i]);
				i++;
			}
			s_new[i] = '\0';
			return (s_new);
		}
		else
			return (NULL);
	}
	return (0);
}
