/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:45:52 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/07 18:03:08 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int t;

	t = (unsigned int)n;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		t = t * -1;
		ft_putnbr_fd(t, fd);
	}
	else if (t > 9)
	{
		ft_putnbr_fd(t / 10, fd);
		ft_putnbr_fd(t % 10, fd);
	}
	else
		ft_putchar_fd(t + '0', fd);
}
