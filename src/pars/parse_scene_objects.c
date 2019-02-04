/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 20:34:43 by vmartynu          #+#    #+#             */
/*   Updated: 2018/07/15 16:15:48 by vmartynu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_composed_objects(char *index, char *sub, int i, t_sdl *sd)
{
	if (!ft_strncmp(index, "type=\"bocal\"", 12))
		parse_bocal(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"tunel\"", 12))
		parse_tunel(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"disk\"", 11))
		parse_disk(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"cone_closed\"", 18))
		parse_cone_closed(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"cylinder_closed\"", 22))
		parse_cylinder_closed(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"triangle\"", 15))
		parse_triangle(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"tetragon\"", 15))
		parse_tetragon(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"box\"", 10))
		parse_box(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"mandelbulb\"", 17))
		parse_mandelbulb(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"torus88\"", 14))
		parse_torus88(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"heart\"", 12))
		parse_heart(sub, i, sd);
	else
		return (0);
	return (1);
}

static int		check_for_ob(char *index, char *sub, int i, t_sdl *sd)
{
	if (!index)
		return (0);
	if (!ft_strncmp(index, "type=\"sphere\"", 13))
		parse_sphere(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"plane\"", 12))
		parse_plane(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"ellipsoid\"", 16))
		parse_ellipsoid(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"torus\"", 12))
		parse_torus(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"tunel\"", 12))
		parse_tunel(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"paraboloid\"", 17))
		parse_paraboloid(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"cylinder\"", 15))
		parse_cylinder(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"perfcube\"", 15))
		parse_perfcube(sub, i, sd);
	else if (!ft_strncmp(index, "type=\"cone\"", 11))
		parse_cone(sub, i, sd);
	else if (check_composed_objects(index, sub, i, sd) == 1)
		return (1);
	else
		return (0);
	return (1);
}

static int		c(char *sub, int i, int *count, t_sdl *sd)
{
	if (sd)
		i = 0;
	parse_obj_file(sub, i, sd);
	*count = *count - 1;
	ft_strdel(&sub);
	return (1);
}

static int		delll(char *sub)
{
	ft_strdel(&sub);
	return (1);
}

int				parse_scene_objects(t_sdl *sd, char *scene, int k, int i)
{
	char		*start;
	char		*end;
	char		*index;
	char		*sub;

	sub = NULL;
	index = scene;
	while (++i < k)
	{
		start = ft_strstr(index, "<object ");
		end = ft_strstr(start, "</object>");
		if (start && end && (sub = ft_strsub(start, 0, (end + 9) - start)))
			index = ft_strstr(start, "type=");
		if (check_for_ob(index, sub, i, sd))
			;
		else if (index && !ft_strncmp(index, "type=\"*.obj\"", 11)
				&& c(sub, i, &k, sd))
			continue;
		else if (delll(sub))
			continue;
		ft_strdel(&sub);
		index = end;
	}
	(k > 0) ? sd->obj[0].count = k + sd->count : 0;
	return (0);
}
