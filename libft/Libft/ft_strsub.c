/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 11:32:34 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 18:16:30 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (s)
	{
		ret = (char *)malloc(sizeof(char) * len + 1);
		if (ret)
		{
			while (i < len)
			{
				ret[i] = s[start];
				start++;
				i++;
			}
			ret[i] = '\0';
			return (ret);
		}
		else
			return (NULL);
	}
	return (NULL);
}
