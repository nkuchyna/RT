/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:26:06 by vmartynu          #+#    #+#             */
/*   Updated: 2017/11/11 08:02:20 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*t;
	void	*cont;

	cont = (void *)content;
	t = (t_list *)malloc(sizeof(t_list));
	if (!t)
		return (NULL);
	if (content == NULL)
	{
		t->content = NULL;
		t->content_size = 0;
	}
	else
	{
		if (!(cont = (void *)malloc(content_size)))
		{
			free(t);
			return (NULL);
		}
		ft_memcpy(cont, content, content_size);
		t->content = cont;
		t->content_size = content_size;
	}
	t->next = NULL;
	return (t);
}
