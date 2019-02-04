/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:04:53 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/17 16:09:29 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qsort(int *array, int ft, int lt)
{
	int l;
	int r;
	int m;

	l = ft;
	r = lt;
	m = array[(l + r) / 2];
	while (l <= r)
	{
		while (array[l] < m)
			l++;
		while (array[r] > m)
			r--;
		if (l <= r)
			ft_swap(&array[l++], &array[r--]);
	}
	if (ft < r)
		ft_qsort(array, ft, r);
	if (lt > l)
		ft_qsort(array, l, lt);
}
