/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:27:40 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/17 17:17:30 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushb(t_list **bl, void const *cont, size_t c_size)
{
	t_list *list;

	list = *bl;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_lstnew(cont, c_size);
	}
	else
		*bl = ft_lstnew(cont, c_size);
}
