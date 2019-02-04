/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 15:45:25 by sperkhun          #+#    #+#             */
/*   Updated: 2018/07/27 15:45:26 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_float3	check_col(cl_float3 c)
{
	c.z = c.z > 255 ? 255 : c.z;
	c.z = c.z < 0 ? 0 : c.z;
	c.y = c.y > 255 ? 255 : c.y;
	c.y = c.y < 0 ? 0 : c.y;
	c.x = c.x > 255 ? 255 : c.x;
	c.x = c.x < 0 ? 0 : c.x;
	return (c);
}

static cl_float3	smooth(unsigned char *p, int x, int y, int pitch)
{
	int			i;
	cl_float3	c;

	i = x * 4 + y * pitch;
	c = (cl_float3) {{p[i] * 4, p[i + 1] * 4, p[i + 2] * 4}};
	i = (x - 1) * 4 + (y - 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 1, p[i + 1] * 1, p[i + 2] * 1}});
	i = x * 4 + (y - 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 2, p[i + 1] * 2, p[i + 2] * 2}});
	i = (x + 1) * 4 + (y - 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 1, p[i + 1] * 1, p[i + 2] * 1}});
	i = (x - 1) * 4 + y * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 2, p[i + 1] * 2, p[i + 2] * 2}});
	i = (x + 1) * 4 + y * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 2, p[i + 1] * 2, p[i + 2] * 2}});
	i = (x - 1) * 4 + (y + 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 1, p[i + 1] * 1, p[i + 2] * 1}});
	i = x * 4 + (y + 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 2, p[i + 1] * 2, p[i + 2] * 2}});
	i = (x + 1) * 4 + (y + 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * 1, p[i + 1] * 1, p[i + 2] * 1}});
	c = ft_vector_div(c, 16);
	return (check_col(c));
}

static cl_float3	contouring(unsigned char *p, int x, int y, int pitch)
{
	int			i;
	int			k;
	cl_float3	c;

	k = -1;
	i = x * 4 + y * pitch;
	c = (cl_float3) {{p[i] * 9, p[i + 1] * 9, p[i + 2] * 9}};
	i = (x - 1) * 4 + (y - 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = x * 4 + (y - 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = (x + 1) * 4 + (y - 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = (x - 1) * 4 + y * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = (x + 1) * 4 + y * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = (x - 1) * 4 + (y + 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = x * 4 + (y + 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	i = (x + 1) * 4 + (y + 1) * pitch;
	c = ft_vector_add(c, (cl_float3){{p[i] * k, p[i + 1] * k, p[i + 2] * k}});
	return (check_col(c));
}

static void			change_img(unsigned char *p, cl_float3 *color, int pitch)
{
	int		i;
	int		a;
	int		y;
	int		x;

	y = 0;
	a = 0;
	while (++y < HEIGHT - 1)
	{
		x = 0;
		while (++x < WIDTH - 1)
		{
			i = x * 4 + y * pitch;
			p[i++] = color[a].x;
			p[i++] = color[a].y;
			p[i++] = color[a].z;
			a++;
		}
	}
}

void				cartoon(t_sdl *sd)
{
	cl_float3		color[(WIDTH - 2) * (HEIGHT - 2)];
	unsigned char	*p;
	int				a;
	int				y;
	int				x;

	p = (unsigned char*)sd->screen->pixels;
	y = 0;
	a = -1;
	while (++y < HEIGHT - 1)
	{
		x = 0;
		while (++x < WIDTH - 1 && ++a < (WIDTH - 2) * (HEIGHT - 2))
			color[a] = smooth(p, x, y, sd->screen->pitch);
	}
	change_img(p, color, sd->screen->pitch);
	y = 0;
	a = -1;
	while (++y < HEIGHT - 1)
	{
		x = 0;
		while (++x < WIDTH - 1 && ++a < (WIDTH - 2) * (HEIGHT - 2))
			color[a] = contouring(p, x, y, sd->screen->pitch);
	}
	change_img(p, color, sd->screen->pitch);
}
