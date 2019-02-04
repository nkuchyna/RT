/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:46:31 by vmartynu          #+#    #+#             */
/*   Updated: 2018/05/14 16:36:32 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1 - 1;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char		*option(int n)
{
	char *r;

	r = (char *)malloc(sizeof(char) * 2);
	r[0] = '0';
	r[1] = '\0';
	if (n)
		n = 0;
	return (r);
}

static char		*option2(char *r, int i, int z, int n)
{
	if (n < 0)
	{
		r[i] = '-';
		n = n * -1;
	}
	i = ft_len(z) - 1;
	while (n != 0)
	{
		r[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	r[ft_len(z)] = '\0';
	return (r);
}

char			*ft_itoa(int n)
{
	char	*ret;
	int		i;
	int		z;

	z = n;
	i = 0;
	if (n == 0)
		return (option(n));
	ret = (char *)malloc(sizeof(char) * (ft_len(n) + 1));
	if (!ret)
		return (NULL);
	ret = option2(ret, i, z, n);
	if (z == -2147483648)
		ft_strcpy(ret, "-2147483648");
	return (ret);
}
