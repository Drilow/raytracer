/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 22:16:44 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 23:17:15 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sdl_stuff/sdl_mgr.h>

void			draw_px(SDL_Surface *surf, int x, int y, t_rgb cols)
{
	//t_rgb		cols;
	Uint32		col;
	Uint32		*pxmem;

	//cols.r = color >> 16;
	//cols.g = color >> 8;
	//cols.b = color;
	col = SDL_MapRGB(surf->format,
		cols.r, cols.g, cols.b);
	pxmem = (Uint32*)surf->pixels +
	(y * surf->pitch / surf->format->BytesPerPixel)
	+ x;
	*pxmem = col;
}
