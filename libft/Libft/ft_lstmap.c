/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:46:56 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/17 16:09:02 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*t;

	t = lst;
	if (lst && f)
	{
		new = f(lst);
		t = new;
		while (lst->next)
		{
			lst = lst->next;
			new->next = f(lst);
			new = new->next;
		}
		if (lst->next == NULL)
		{
			new->next = NULL;
		}
		return (t);
	}
	return (NULL);
}
