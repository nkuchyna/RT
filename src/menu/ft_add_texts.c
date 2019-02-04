/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_texts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:42:11 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/04 16:42:24 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_add_texts1(t_sdl *sd, SDL_Color color)
{
	sd->texts[0] = TTF_RenderText_Solid(sd->font, "Effect", color);
	sd->texts[1] = TTF_RenderText_Solid(sd->font, "Sepia", color);
	sd->texts[2] = TTF_RenderText_Solid(sd->font, "B/W", color);
	sd->texts[3] = TTF_RenderText_Solid(sd->font, "Cart", color);
	sd->texts[4] = TTF_RenderText_Solid(sd->font, "Def", color);
	sd->texts[5] = TTF_RenderText_Solid(sd->font, "Obj", color);
	sd->texts[6] = TTF_RenderText_Solid(sd->font, "Mater", color);
	sd->texts[7] = TTF_RenderText_Solid(sd->font, "Text", color);
	sd->texts[8] = TTF_RenderText_Solid(sd->font, "Pos", color);
	sd->texts[9] = TTF_RenderText_Solid(sd->font, "Dir", color);
	sd->texts[10] = TTF_RenderText_Solid(sd->font, "  -", color);
	sd->texts[11] = TTF_RenderText_Solid(sd->font, "x/r", color);
	sd->texts[12] = TTF_RenderText_Solid(sd->font, "  +", color);
	sd->texts[13] = TTF_RenderText_Solid(sd->font, "  -", color);
	sd->texts[14] = TTF_RenderText_Solid(sd->font, "y/g", color);
	sd->texts[15] = TTF_RenderText_Solid(sd->font, "  +", color);
	sd->texts[16] = TTF_RenderText_Solid(sd->font, "  -", color);
	sd->texts[17] = TTF_RenderText_Solid(sd->font, "z/b", color);
	sd->texts[18] = TTF_RenderText_Solid(sd->font, "  +", color);
}

static void	ft_add_texts2(t_sdl *sd, SDL_Color color)
{
	sd->texts[19] = TTF_RenderText_Solid(sd->font, "D", color);
	sd->texts[20] = TTF_RenderText_Solid(sd->font, "T", color);
	sd->texts[21] = TTF_RenderText_Solid(sd->font, "1", color);
	sd->texts[22] = TTF_RenderText_Solid(sd->font, "2", color);
	sd->texts[23] = TTF_RenderText_Solid(sd->font, "M", color);
	sd->texts[24] = TTF_RenderText_Solid(sd->font, "G", color);
	sd->texts[25] = TTF_RenderText_Solid(sd->font, "3", color);
	sd->texts[26] = TTF_RenderText_Solid(sd->font, "4", color);
	sd->texts[27] = TTF_RenderText_Solid(sd->font, "DM", color);
	sd->texts[28] = TTF_RenderText_Solid(sd->font, "DT", color);
	sd->texts[29] = TTF_RenderText_Solid(sd->font, "5", color);
	sd->texts[30] = TTF_RenderText_Solid(sd->font, "D", color);
	sd->texts[31] = TTF_RenderText_Solid(sd->font, "+", color);
	sd->texts[32] = TTF_RenderText_Solid(sd->font, "-", color);
	sd->texts[33] = TTF_RenderText_Solid(sd->font, "Col", color);
	sd->texts[34] = TTF_RenderText_Solid(sd->font, "Samp: 1", color);
	sd->texts[35] = TTF_RenderText_Solid(sd->font, "Screenshot", color);
}

void		ft_add_texts(t_sdl *sd)
{
	SDL_Color		color;

	color = sd->t_color;
	ft_add_texts1(sd, color);
	ft_add_texts2(sd, color);
}
