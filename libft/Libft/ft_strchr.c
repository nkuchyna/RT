/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:23:07 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/09 14:06:28 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ser;

	i = 0;
	ser = (char *)s;
	while (ser[i] != '\0')
	{
		if (ser[i] == c)
			return (&ser[i]);
		i++;
	}
	if (c == '\0')
		return (&ser[i]);
	return (NULL);
}
