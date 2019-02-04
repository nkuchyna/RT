/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:31:14 by vmartynu          #+#    #+#             */
/*   Updated: 2018/05/14 16:39:26 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_powp(float a, int n)
{
	float	ret;
	int		n_;

	ret = a;
	if (n == 0)
		return (1);
	if (n == 1)
		return (a);
	if (n > 1)
	{
		n_ = n - 1;
		while (n_--)
			ret = ret * a;
		return (ret);
	}
	else
		return (-1);
}

static float	ft_pow(float a, int n)
{
	if (n >= 0)
		return (ft_powp(a, n));
	else
		return (1 / ft_powp(a, (n * -1)));
}

double			ft_atof(char *s)
{
	double	i;
	int		a;
	int		l;

	i = ft_atoi(s);
	a = -1;
	l = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		l = *s == '-' && !i ? -1 : 1;
		s++;
	}
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
		s++;
	while (ft_isdigit(*s))
	{
		i += (*s - 48) * ft_pow(10, a);
		s++;
		a--;
	}
	return (i * l);
}
