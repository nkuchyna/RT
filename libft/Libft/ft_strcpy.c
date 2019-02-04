/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 13:11:07 by vmartynu          #+#    #+#             */
/*   Updated: 2017/10/30 15:19:50 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *destptr, const char *srcptr)
{
	int i;

	i = 0;
	while (srcptr[i] != '\0')
	{
		destptr[i] = srcptr[i];
		i++;
	}
	destptr[i] = '\0';
	return (destptr);
}
