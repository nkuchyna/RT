/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_obj_mater.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:47:19 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/02 18:47:33 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_change_obj_texture(int id_param, t_obj *obj)
{
	if (id_param == 12)
	{
		obj->pattern = -1;
		return ;
	}
	obj->pattern = id_param - 6;
}

static void	ft_change_def_comp(float *diffuse, int k, float shift)
{
	*diffuse += shift * k;
	if (*diffuse > 1)
		*diffuse = 1;
	else if (*diffuse < 0)
		*diffuse = 0;
}

static void	ft_change_sub_params(int k, int id_param, t_obj *obj)
{
	int		shift;

	shift = 10;
	if (id_param == 4 && obj->cos_pow < 100000)
	{
		if (obj->cos_pow < 100)
			obj->cos_pow += k * shift;
		else if (obj->cos_pow > 100 && obj->cos_pow < 1000)
			obj->cos_pow += k * shift * 5;
		else
			shift *= shift;
		if (obj->cos_pow < 0)
			obj->cos_pow = 0;
	}
	else if (id_param == 5 || id_param == 6)
		ft_change_def_comp(&obj->diffuse, k, 0.02);
}

static void	ft_change_complex_mater(int k, int id, int id_param, t_obj *obj)
{
	if (id_param == 4 && !(id == 31 || id == 32))
	{
		obj->refl_type = 2;
		obj->diffuse = 0;
		obj->cos_pow = 256;
	}
	else if (id_param == 5 && !(id == 31 || id == 32))
	{
		obj->refl_type = 3;
		obj->diffuse = 0.5;
	}
	else if (id_param == 6 && !(id == 31 || id == 32))
	{
		obj->refl_type = 5;
		obj->diffuse = 0.5;
		obj->refraction = 1.4;
	}
	else if (id_param >= 4 && id_param <= 6 && (id == 31 || id == 32))
		ft_change_sub_params(k, id_param, obj);
}

void		ft_change_obj_mater(int k, int id, int id_param, t_obj *obj)
{
	if (id_param == 1)
	{
		obj->refl_type = 0;
		obj->diffuse = 1;
	}
	else if (id_param == 2)
	{
		obj->refl_type = 4;
		obj->refraction = 1.4;
	}
	else if (id_param == 3)
	{
		obj->refl_type = 1;
		obj->diffuse = 0;
	}
	ft_change_complex_mater(k, id, id_param, obj);
}
