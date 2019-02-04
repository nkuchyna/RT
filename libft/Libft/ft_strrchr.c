/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:52:12 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/03 17:08:41 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;
	char	*ser;

	ser = (char*)s;
	i = 0;
	temp = NULL;
	while (ser[i] != '\0')
	{
		if (ser[i] == c)
			temp = &ser[i];
		if (ser[i + 1] == c)
			temp = &ser[i + 1];
		i++;
	}
	return (temp);
}
