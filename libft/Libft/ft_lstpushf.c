/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:31:41 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/17 17:40:42 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushf(t_list **bl, void const *cont, size_t c_size)
{
	t_list *list;
	t_list *temp;

	temp = *bl;
	if (temp)
	{
		list = ft_lstnew(cont, c_size);
		*bl = list;
		list->next = temp;
	}
	else
		*bl = ft_lstnew(cont, c_size);
}
