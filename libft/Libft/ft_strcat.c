/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:51:02 by vmartynu          #+#    #+#             */
/*   Updated: 2017/10/30 09:02:23 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *append)
{
	int		i;
	int		j;
	char	*ap;

	ap = (char *)append;
	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (ap[j] != '\0')
	{
		dest[i] = ap[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
