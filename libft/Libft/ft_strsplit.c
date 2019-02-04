/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 08:13:50 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/11 09:33:04 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			cw(char const *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			j++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (j);
}

static int			wordlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static char			**ss(char **strspl, char const *s, char c, int i)
{
	int j;
	int k;
	int count;

	count = cw(&s[i], c);
	j = 0;
	while (j < count)
	{
		k = 0;
		strspl[j] = (char *)malloc(sizeof(char) * (wordlen(&s[i], c) + 1));
		while (s[i] != c && s[i] != '\0')
		{
			strspl[j][k] = s[i];
			i++;
			k++;
		}
		strspl[j][k] = '\0';
		while (s[i] == c && s[i] != '\0')
			i++;
		j++;
	}
	strspl[j] = NULL;
	return (strspl);
}

char				**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**strsplited;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == c && s[i] != '\0')
		i++;
	strsplited = (char **)malloc(sizeof(strsplited) * (cw(&s[i], c) + 8));
	if (!strsplited)
		return (NULL);
	return (ss(strsplited, s, c, i));
}
