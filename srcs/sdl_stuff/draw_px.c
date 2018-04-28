/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 22:16:44 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 22:17:08 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			draw_px(SDL_Surface *surf, int x, int y, int color)
{
	t_rgb		cols;
	Uint32		col;
	Uint32		*pxmem;

	cols.r = color >> 16;
	cols.g = color >> 8;
	cols.b = color;
	col = SDL_MapRGB(surf->format,
		cols.r, cols.g, cols.b);
	pxmem = (Uint32*)surf->pixels +
	(y * surf->pitch / surf->format->BytesPerPixel)
	+ x;
	*pxmem = col;
}
