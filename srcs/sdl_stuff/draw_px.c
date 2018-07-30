/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 22:16:44 by adleau            #+#    #+#             */
/*   Updated: 2018/07/30 07:06:18 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sdl_stuff/sdl_mgr.h>
#include <gtk/gtk.h>

void				draw_px_new(unsigned char *buf, int x, int y, t_rgb cols)
{
	unsigned char	c;
	unsigned char	*ptr;

	c = 0;
	c += cols.r * 65536;
	c += cols.g * 256;
	c += cols.b;
	ptr = buf + (y * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W) / CAIRO_FORMAT_RGB24) + x;
	*ptr = c;
}

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
