/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_button_action.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 18:12:17 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/02 18:27:18 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_define_sel_param(int button, int param)
{
	int		flag;
	int		i;
	int		*str;

	flag = 0;
	i = 0;
	str = malloc(sizeof(int) * 15);
	str = (int[15]){19, 20, 23, 24, 27, 28, 21, 22, 25, 26, 29, 30, 8, 9, 33};
	if (button == -1)
		flag = 1;
	if (flag == 1)
	{
		return (str[param]);
	}
	else if (flag == 0)
	{
		while (i < PARAM_NBR)
		{
			if (str[i] == button)
				return (i + 1);
			i++;
		}
	}
	return (button);
}

int		ft_def_change_par_buttom(int id, int id_sel_par)
{
	int		param;

	param = ft_define_sel_param(id, -1);
	if ((id == 31 || id == 32) && id_sel_par >= 1 && id_sel_par <= 12)
		return (1);
	if (id_sel_par >= 13 && id_sel_par <= 15 && (id == 10 || id == 12
	|| id == 13 || id == 15 || id == 16 || id == 18))
		return (1);
	if (id == 21 || id == 22
	|| id == 25 || id == 26 || id == 29 || id == 30)
		return (1);
	if (id == 19 || id == 20
	|| id == 23 || id == 24 || id == 27 || id == 28)
		return (1);
	return (0);
}

int		ft_define_select_rect(int x, int y, SDL_Rect *menu)
{
	int		id_select_rect;
	int		i;

	i = -1;
	id_select_rect = -1;
	while (++i < MENU_RECT_NBR)
	{
		if (x >= menu[i].x && x <= (menu[i].x + menu[i].w)
		&& y >= menu[i].y && y <= (menu[i].y + menu[i].h))
			id_select_rect = i;
	}
	return (id_select_rect);
}

void	ft_menu_button_action(t_sdl *sd, int select_flag)
{
	int			id;

	id = sd->id_sel_rect;
	if (id > 0 && id <= 4)
	{
		sd->effect = id;
		return ;
	}
	if ((id >= 1 && id <= 4) || id == 35)
		sd->id_sel_par = 0;
	if (((id >= 19 && id <= 30) || id == 8 || id == 9 || id == 33)
	&& sd->id_sel_obj != -1)
		sd->id_sel_par = ft_define_sel_param(id, -1);
	if (select_flag == 1 && sd->id_sel_par != 0
	&& ft_def_change_par_buttom(id, sd->id_sel_par) == 1)
		ft_change_obj_params(&sd->obj[sd->id_sel_obj], sd->id_sel_rect,
							sd->id_sel_par);
}
