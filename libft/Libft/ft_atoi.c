/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:15:58 by vmartynu          #+#    #+#             */
/*   Updated: 2018/05/07 17:01:46 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int					skipo(const char *st)
{
	int i;

	i = 0;
	while (((st[i] == ' ' || st[i] == '\t' || st[i] == '\n') ||
		(st[i] == '\v' || st[i] == '\f' || st[i] == '\r')) && (st[i] != '\0'))
		i++;
	return (i);
}

static unsigned long int	check(unsigned long int rez, int k)
{
	if (rez >= 9223372036854775807 && k == 1)
		return (-1);
	else if (rez > 9223372036854775807 && k == -1)
		return (0);
	else
		return (rez);
}

int							ft_atoi(const char *st)
{
	int					i;
	unsigned long int	rez;
	int					k;

	rez = 0;
	k = 1;
	i = skipo(st);
	if (st[i] == '-')
	{
		k = -1;
		i++;
	}
	else if (st[i] == '+')
	{
		k = 1;
		i++;
	}
	while (st[i] >= 48 && 57 >= st[i] && st[i] != '\0')
	{
		rez = rez * 10 + st[i] - 48;
		i++;
	}
	rez = check(rez, k);
	return (rez * k);
}
