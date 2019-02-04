/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:51:03 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/11 10:03:18 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*triming(char *s, char *st, int i, int j)
{
	int k;

	k = 0;
	while (i <= j)
	{
		st[k] = s[i];
		i++;
		k++;
	}
	st[k] = '\0';
	return (st);
}

char		*ft_strtrim(char *s)
{
	int		i;
	int		j;
	char	*s_trim;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		s_trim = (char *)malloc(sizeof(char));
		s_trim[0] = '\0';
		return (s_trim);
	}
	j = ft_strlen(s) - 1;
	if (i == j)
		return (NULL);
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
		j--;
	s_trim = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!s_trim)
		return (NULL);
	return (triming(s, s_trim, i, j));
}
