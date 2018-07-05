/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 22:52:03 by alacrois          #+#    #+#             */
/*   Updated: 2018/07/05 02:57:01 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <display/display.h>
#include <global.h>
#include <sdl_stuff/sdl_mgr.h>


#include <stdio.h>
//#include <gl_handling/gl_includes.h>
#include <objects/object.h>
#include <cl_inc/cl_defs.h>
#include <geometry/geometry.h>
#include <extra/extra_defs.h>
#include <libft.h>
#include <parser/parser.h>

static t_rgb	get_pixel(SDL_Surface *surf, int x, int y)
{
	t_rgb		pixel;
	Uint32		*intpixel;
	Uint8		components[3];

	intpixel = (Uint32*)surf->pixels +
		(y * surf->pitch / surf->format->BytesPerPixel) + x;
	SDL_GetRGB(*intpixel, surf->format, &(components[0]), &(components[1]), &(components[2]));
	pixel.r = components[0];
	pixel.g = components[1];
	pixel.b = components[2];
	pixel.trans = 0;
	return (pixel);
}

void			antialiasing(t_sdl_wrapper *e)
{
	t_point		p;
	t_rgb		new_color;

	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			new_color = get_pixel(e->surf, p.x, p.y);
//			if (p.x % 5 == 0)
//				new_color = ft_rgb(0, 0, 255, 0);
			draw_px(e->surf, p.x, p.y, new_color);
		}
	}
}
