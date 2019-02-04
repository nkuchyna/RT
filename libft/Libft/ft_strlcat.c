/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:38:56 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 18:03:38 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *app, size_t size)
{
	size_t k;

	if (size <= ft_strlen(dest))
		return (ft_strlen((char*)app) + size);
	k = ft_strlen(dest) + ft_strlen(app);
	while (size && *dest)
	{
		size--;
		dest++;
	}
	while (size-- > 1 && *app)
	{
		*dest = *app;
		dest++;
		app++;
	}
	*dest = '\0';
	return (k);
}
