/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:28:51 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 18:09:59 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	t;

	t = (unsigned int)n;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
	}
	else if (n < 0)
	{
		ft_putchar('-');
		t = t * -1;
		ft_putnbr(t);
	}
	else if (t > 9)
	{
		ft_putnbr(t / 10);
		ft_putnbr(t % 10);
	}
	else
	{
		ft_putchar(t + '0');
	}
}
