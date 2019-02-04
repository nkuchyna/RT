/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:29:25 by vmartynu          #+#    #+#             */
/*   Updated: 2018/01/09 17:21:26 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str)
	{
		i = 0;
		while (src[i])
		{
			str[i] = src[i];
			i++;
		}
		str[i] = '\0';
	}
	else
		return (NULL);
	return (str);
}
