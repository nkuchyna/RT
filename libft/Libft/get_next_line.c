/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 09:12:45 by vmartynu          #+#    #+#             */
/*   Updated: 2018/02/02 12:12:11 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static t_fd		*new_f(const int fd)
{
	t_fd *s;

	s = (t_fd *)ft_memalloc(sizeof(t_fd));
	s->fd = fd;
	s->s = NULL;
	s->bl = NULL;
	s->next = NULL;
	s->ret = BUFF_SIZE;
	return (s);
}

static t_fd		*check_f(t_fd *f, const int fd)
{
	if (!f)
	{
		f = new_f(fd);
		f->bl = f;
		return (f);
	}
	while (f)
	{
		if (f->fd == fd)
			return (f);
		if (f->next == NULL)
		{
			f->next = new_f(fd);
			f->next->bl = f->bl;
			return (f->next);
		}
		f = f->next;
	}
	return (NULL);
}

static void		option_1(char *buf, char **line, t_fd *f, char *t)
{
	if (!ft_memchr(buf, '\n', ft_strlen(buf)))
	{
		if (!f->s)
			f->s = ft_strsub(buf, 0, BUFF_SIZE);
		else
		{
			t = ft_strjoin(f->s, buf);
			free(f->s);
			f->s = t;
		}
	}
	else
	{
		if (!f->s)
			*line = ft_strsub(buf, 0, (char *)ft_strchr(buf, '\n') - buf);
		else
		{
			t = ft_strsub(buf, 0, ft_strchr(buf, '\n') - buf);
			*line = ft_strjoin(f->s, t);
			free(f->s);
			free(t);
		}
	}
}

static int		option_2(char *buf, char **line, t_fd *f, char *t)
{
	while ((f->ret = read(f->fd, buf, BUFF_SIZE)))
	{
		buf[f->ret] = '\0';
		if (f->ret == -1)
			return (-1);
		option_1(buf, line, f, t);
		if (ft_memchr(buf, '\n', ft_strlen(buf)))
		{
			f->s = ft_strsub(buf, ft_strchr(buf, '\n') + 1
		- buf, BUFF_SIZE - 1 - (ft_strchr(buf, '\n') - buf));
			return (1);
		}
	}
	if (f->ret == 0 && f->s)
	{
		if (*(f->s) == '\0')
			return (0);
		*line = f->s;
		f->s = NULL;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_fd	*f = NULL;
	char		buf[BUFF_SIZE + 1];
	char		*t;

	t = NULL;
	if (f)
		f = f->bl;
	f = check_f(f, fd);
	if (f->fd < 0 || !line)
		return (-1);
	if (f->s && ft_memchr(f->s, '\n', ft_strlen(f->s)))
	{
		*line = ft_strsub(f->s, 0, ft_strchr(f->s, '\n') - f->s);
		f->s = ft_strsub(f->s, ft_strchr(f->s, '\n')
		+ 1 - f->s, ft_strlen(f->s));
		if (f->ret == 0 && f->s)
		{
			if (*(f->s) == '\0')
				return (0);
			*line = f->s;
		}
		return (1);
	}
	return (option_2(buf, line, f, t));
}
