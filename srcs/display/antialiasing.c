/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 22:52:03 by alacrois          #+#    #+#             */
/*   Updated: 2018/07/08 16:45:02 by alacrois         ###   ########.fr       */
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

static t_rgb	two_colors_average(t_rgb a, t_rgb b, double ratio)
{
	return (ft_rgb((a.r * ratio) + (b.r * (1 - ratio)), \
				   (a.g * ratio) + (b.g * (1 - ratio)), \
				   (a.b * ratio) + (b.b * (1 - ratio)), \
				   (a.trans * ratio) + (b.trans * (1 - ratio))));
}


static t_rgb	color_average(t_rgb *colors, int size)
{
	int			i;
	t_rgb		ca;

	i = -1;
	ca = ft_rgb(0, 0, 0, 0);
	while (++i)
		ca = ft_rgb(ca.r + (colors[i].r / size), ca.g + (colors[i].g / size), \
			ca.b + (colors[i].b / size), ca.trans + (colors[i].trans / size));
	return (ca);
}

static double	colorcmp(t_rgb a, t_rgb b)
{
	t_rpoint	cmp;

	cmp.x = 1 - ((double)ft_abs(a.r - b.r) / 255);
	cmp.y = 1 - ((double)ft_abs(a.g - b.g) / 255);
	cmp.z = 1 - ((double)ft_abs(a.b - b.b) / 255);
//	printf("colorcmp = %f\n", (cmp.x + cmp.y + cmp.z) / 3);
	return ((cmp.x + cmp.y + cmp.z) / 3);
}

static int		detect_edge(t_point p, t_sdl_wrapper *e)
{
	t_rgb		pix;
	t_rgb		adjacent[4];
	int			i;

	pix = get_pixel(e->surf, p.x, p.y);
	i = -1;
	while (++i < 4)
		adjacent[i] = pix;
	if (p.y > 0)
		adjacent[0] = get_pixel(e->surf, p.x, p.y - 1);
	if (p.x + 1 < WIN_W)
		adjacent[1] = get_pixel(e->surf, p.x + 1, p.y);
	if (p.y + 1 < WIN_H)
		adjacent[1] = get_pixel(e->surf, p.x, p.y + 1);
	if (p.x > 0)
		adjacent[3] = get_pixel(e->surf, p.x - 1, p.y);
	if (colorcmp(adjacent[0], adjacent[1]) > AA_UPPER_THRESHOLD && \
		colorcmp(pix, two_colors_average(adjacent[0], adjacent[1], 0.5)) < AA_LOWER_THRESHOLD)
		return (1);
	if (colorcmp(adjacent[1], adjacent[2]) > AA_UPPER_THRESHOLD && \
		colorcmp(pix, two_colors_average(adjacent[1], adjacent[2], 0.5)) < AA_LOWER_THRESHOLD)
		return (1);
	if (colorcmp(adjacent[2], adjacent[3]) > AA_UPPER_THRESHOLD && \
		colorcmp(pix, two_colors_average(adjacent[2], adjacent[3], 0.5)) < AA_LOWER_THRESHOLD)
		return (1);
	if (colorcmp(adjacent[3], adjacent[0]) > AA_UPPER_THRESHOLD && \
		colorcmp(pix, two_colors_average(adjacent[3], adjacent[0], 0.5)) < AA_LOWER_THRESHOLD)
		return (1);
	return (0);
}

static void		apply_aa(t_point p, t_sdl_wrapper *e, t_rgb **pixdup)
//static void		apply_aa(t_point p, t_sdl_wrapper *e, t_rgb[WIN_H][WIN_W] pixdup)
{
	t_rgb		pix;
	t_rgb		adj[8];
	int			i;

	pix = pixdup[p.y][p.x];
	i = -1;
	while (++i < 8)
		adj[i] = pixdup[p.y][p.x];
	if (p.y > 0 && p.x > 0)
		adj[0] = pixdup[p.y - 1][p.x - 1];
	if (p.y > 0)
		adj[1] = pixdup[p.y - 1][p.x];
	if (p.y > 0 && p.x + 1 < WIN_W)
		adj[2] = pixdup[p.y - 1][p.x + 1];
	if (p.x + 1 < WIN_W)
		adj[3] = pixdup[p.y][p.x + 1];
	if (p.y + 1 < WIN_H && p.x + 1 < WIN_W)
		adj[4] = pixdup[p.y + 1][p.x + 1];
	if (p.y + 1 < WIN_H)
		adj[5] = pixdup[p.y + 1][p.x];
	if (p.y + 1 < WIN_H && p.x > 0)
        adj[6] = pixdup[p.y + 1][p.x - 1];
	if (p.x > 0)
        adj[7] = pixdup[p.y][p.x - 1];
	draw_px(e->surf, p.x, p.y, two_colors_average(pix, color_average(adj, 8), 0.3));
//	draw_px(e->surf, p.x, p.y, color_average(adj, 8));
//	draw_px(e->surf, p.x, p.y, two_colors_average(two_colors_average(pix, color_average(adj, 8), 0.5), pix, 0.5));
//	draw_px(e->surf, p.x, p.y, ft_rgb(255, 0, 175, 0));
//	draw_px(e->surf, p.x, p.y, pix);
}

void			antialiasing(t_sdl_wrapper *e)
{
	t_point		p;
//	t_rgb		new_color;
	int			aa[WIN_H][WIN_W];
	t_rgb		**pixdup;

	printf("ut = %f && lt = %f\n", AA_UPPER_THRESHOLD, AA_LOWER_THRESHOLD);
	p.y = -1;
	if (!(pixdup = (t_rgb **)malloc(sizeof(t_rgb *) * WIN_H)))
		ft_exit("malloc error", 0);
	while (++p.y < WIN_H)
	{
		p.x = -1;
		if (!(pixdup[p.y] = (t_rgb *)malloc(sizeof(t_rgb) * WIN_W)))
			ft_exit("malloc error", 0);
		while (++p.x < WIN_W)
		{
			pixdup[p.y][p.x] = get_pixel(e->surf, p.x, p.y);
			aa[p.y][p.x] = detect_edge(p, e);
//			if (aa[p.y][p.x] == 1)
//				ft_putendl("edge !");
//			draw_px(e->surf, p.x, p.y, new_color);
		}
	}
	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			if (aa[p.y][p.x] == 1)
			{
				apply_aa(p, e, (t_rgb **)pixdup);
			}
		}
	}
	// FREE pixdup !
}
