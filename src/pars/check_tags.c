/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 12:01:24 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 12:34:49 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				free_it(char *one, char *two, char *three)
{
	if (one)
		ft_strdel(&one);
	if (two)
		ft_strdel(&two);
	if (three)
		ft_strdel(&three);
	return (1);
}

static char		*entrance(char *intag)
{
	while (*intag != '<' && *intag != '\0')
		intag++;
	return (intag);
}

static int		exit_tag(char *intag)
{
	int			i;

	i = 0;
	while (intag[i] != '>' && intag[i] != '\0')
		i++;
	return (i);
}

static void		find_objects(char *intag, char **subj, int i, int *count)
{
	char		*begin;
	int			ret;

	begin = ft_strsub(intag, 0, i + 1);
	(!(ret = ft_strncmp("<object ", begin, 8))) ? (count[0]++) : 0;
	(!ft_strncmp("<light>", begin, 7)) ? count[1]++ : 0;
	(!ft_strncmp("<texture>", begin, 9)) ? count[2]++ : 0;
	(!ft_strncmp("<bump>", begin, 6)) ? count[3]++ : 0;
	if (!ret)
		*subj = ft_strdup("</object>");
	else
		*subj = ft_strjoin("</", &begin[1]);
	ft_strdel(&begin);
}

int				chk_tg(char *save, int *count, char *in, int r)
{
	char		*beg;
	char		*subj;
	int			i;

	in = save;
	while (in)
	{
		if (*(in = entrance(in)) == '\0' && free_it(save, NULL, NULL))
			return (0);
		if ((in[(i = exit_tag(in))]) == '\0' && free_it(save, NULL, NULL))
			return (-1);
		find_objects(in, &subj, i, count);
		if ((beg = ft_strstr(in, subj)))
		{
			r = chk_tg(ft_strsub(in, i + 1, beg - &in[i + 1]), count, NULL, 1);
			if (r == -1 && free_it(save, NULL, subj))
				return (-1);
			in = beg + (ft_strlen(subj));
		}
		else if (free_it(save, NULL, subj))
			return (-1);
		free_it(NULL, subj, NULL);
	}
	ft_strdel(&save);
	return (0);
}
