/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 09:14:29 by vmartynu          #+#    #+#             */
/*   Updated: 2017/12/27 14:29:00 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_fd
{
	int				fd;
	int				ret;
	char			*s;
	struct s_fd		*next;
	struct s_fd		*bl;
}					t_fd;
int					get_next_line(const int fd, char **line);

#endif
