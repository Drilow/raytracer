/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 22:52:03 by alacrois          #+#    #+#             */
/*   Updated: 2018/06/29 17:00:56 by alacrois         ###   ########.fr       */
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

	printf("x = %d, y = %d\n", x, y);
	ft_putendl("debug 1");
	intpixel = (Uint32*)surf->pixels +
		(y * surf->pitch / surf->format->BytesPerPixel) + x;
	printf("*intpixel = %u\n", *intpixel);
	if (*intpixel > 4294967295)
		ft_exit("C'est trop grand !!!", 0);
//	if (*intpixel < 0)
	//       ft_exit("C'est trop petit !!!", 0);
	ft_putendl("debug 2");
	SDL_GetRGB(*intpixel, surf->format, &(components[0]), &(components[1]), &(components[2]));
//	SDL_GetRGB(0, surf->format, &(components[0]), &(components[1]), &(components[2]));
	ft_putendl("debug 3");
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

//	ft_putendl("debug 1");
	p.y = -1;
	while (p.y++ < WIN_H)
	{
		p.x = -1;
//		ft_putendl("debug 2");
		while (++p.x < WIN_W)
		{
//			ft_putendl("debug 1");
			new_color = get_pixel(e->surf, p.x, p.y);
//			ft_putendl("debug 2");
			draw_px(e->surf, p.x, p.y, new_color);
//			ft_putendl("debug 3");
		}
	}
//	ft_putendl("debug 3");
}
