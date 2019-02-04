/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:51:28 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/09 10:51:02 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	temp = *alst;
	if (alst && del)
	{
		while (temp)
		{
			*alst = temp;
			del(temp->content, temp->content_size);
			ft_memdel((void**)alst);
			temp = temp->next;
		}
	}
}
