/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:25:33 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/16 13:40:27 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_float3	str_to_vector(char *s)
{
	cl_float3	ret;
	char		**st;
	int			i;

	i = 0;
	st = ft_strsplit(s, ' ');
	ret.x = ft_atof(st[1]);
	ret.y = ft_atof(st[2]);
	ret.z = ft_atof(st[3]);
	while (st[i])
		ft_strdel(&st[i++]);
	free(st);
	st = NULL;
	return (ret);
}

static void			parse_f_obj(int *ret, char **st, int i, t_o *o)
{
	while (st[i])
		i++;
	if (i == 4 || i == 5)
	{
		ret[0] = 3;
		ret[1] = ft_atoi(st[1]);
		ret[2] = ft_atoi(st[2]);
		ret[3] = ft_atoi(st[3]);
		o->fl = 1;
	}
	else
		free(ret);
}

static int			*fstr_to_arr(char *s, t_o *o)
{
	int				*ret;
	char			**st;
	int				i;

	ret = (int*)ft_memalloc(sizeof(int) * 5);
	i = 0;
	st = ft_strsplit(s, ' ');
	parse_f_obj(ret, st, i, o);
	i = 0;
	while (st[i])
	{
		ft_strdel(&st[i]);
		i++;
	}
	free(st);
	st = NULL;
	return (ret);
}

static void			init_t_o(t_o *ret, int *i)
{
	ret->max = 0;
	ret->min = 0;
	ret->v = (cl_float3*)ft_memalloc(sizeof(cl_float3) * i[0]);
	ret->sharp = (char**)ft_memalloc(sizeof(char*) * i[1]);
	ret->f = (int**)ft_memalloc(sizeof(int*) * i[2]);
	ret->vn = (cl_float3*)ft_memalloc(sizeof(cl_float3) * i[3]);
	ret->vt = (cl_float3*)ft_memalloc(sizeof(cl_float3) * i[4]);
}

t_o					get_obj_data(char *s, int *i)
{
	t_o				ret;
	char			**str;
	int				k;
	int				inc;

	init_int_array(ret.c, 4, 0);
	str = ft_strsplit(s, '\n');
	init_t_o(&ret, i);
	inc = 0;
	while (str[inc])
	{
		k = 0;
		if (str[inc][0] == 'v')
			ret.v[ret.c[0]++] = str_to_vector(str[inc]);
		if (!ft_strncmp(str[inc], "vn", 2))
			ret.vn[ret.c[1]++] = str_to_vector(str[inc]);
		if (!ft_strncmp(str[inc], "vt", 2))
			ret.vt[ret.c[2]++] = str_to_vector(str[inc]);
		if (str[inc][0] == 'f')
			ret.f[ret.c[3]++] = fstr_to_arr(str[inc], &ret);
		free(str[inc]);
		inc++;
	}
	free(str);
	return (ret);
}
