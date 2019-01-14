/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 22:52:03 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/14 01:40:33 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <display/display.h>
#include <global.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <objects/object.h>
//#include <cl_inc/cl_defs.h>
#include <geometry/geometry.h>
#include <extra/extra_defs.h>
#include <libft.h>
#include <parser/parser.h>

extern t_global	g_global;

static t_rgb	get_pixel(unsigned char *buf, int x, int y)
{
	unsigned char	*ptr;
	t_rgb		px;
	int			stride;
	int			bpp;

	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	bpp = stride / WIN_W;
	ptr = buf + (y * stride) + x * bpp;
	px.r = ptr[2];
	px.g = ptr[1];
	px.b = ptr[0];
	px.trans = 0;
	return (px);
}

static t_rgb	two_colors_average(t_rgb a, t_rgb b, double ratio)
{
	return (ft_rgb((a.r * ratio) + (b.r * (1 - ratio)), \
				   (a.g * ratio) + (b.g * (1 - ratio)), \
				   (a.b * ratio) + (b.b * (1 - ratio)), \
				   (a.trans * ratio) + (b.trans * (1 - ratio))));
}


/*
Fonction inutile pour l'instant :

static t_rgb	color_average(t_rgb *colors, int size)
{
	int			i;
	t_rgb		ca;

	i = -1;
	ca = ft_rgb(0, 0, 0, 0);
	while (++i < size)
		ca = ft_rgb(ca.r + (colors[i].r / size), ca.g + (colors[i].g / size), \
			ca.b + (colors[i].b / size), ca.trans + (colors[i].trans / size));
	return (ca);
}
*/

static double	colorcmp(t_rgb a, t_rgb b)
{
	t_rpoint	cmp;
	double		clr_cmp;
	double		brightness_cmp;

	cmp.x = 1 - ((double)ft_abs(a.r - b.r) / 255);
	cmp.y = 1 - ((double)ft_abs(a.g - b.g) / 255);
	cmp.z = 1 - ((double)ft_abs(a.b - b.b) / 255);
	clr_cmp = (cmp.x + cmp.y + cmp.z) / 3;
	brightness_cmp = 1 - ((double)ft_abs(a.r + a.g + a.b - b.r - b.g - b.b) / 765);
	return (clr_cmp * 0.80 + brightness_cmp * 0.20);
}

static int		detect_edge(t_point p)
{
	t_rgb		pix;
	t_rgb		adjacent[4];
	int			i;

	pix = get_pixel(GTKMGR.buf, p.x, p.y);
	i = -1;
	while (++i < 4)
		adjacent[i] = pix;
	if (p.y > 0)
		adjacent[0] = get_pixel(GTKMGR.buf, p.x, p.y - 1);
	if (p.x + 1 < WIN_W)
		adjacent[1] = get_pixel(GTKMGR.buf, p.x + 1, p.y);
	if (p.y + 1 < WIN_H)
		adjacent[1] = get_pixel(GTKMGR.buf, p.x, p.y + 1);
	if (p.x > 0)
		adjacent[3] = get_pixel(GTKMGR.buf, p.x - 1, p.y);
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


static t_rgb	new_color(t_rgb pix, t_rgb *adj)
{
	int			adj1;
	int			adj2;
	double		diff;
	int			i;

	diff = 1;
	i = 1;
	while (i < 8)
	{
		if (colorcmp(pix, adj[i]) < diff)
		{
			diff = colorcmp(pix, adj[i]);
			adj1 = i;
		}
		i = i + 2;
	}
	adj2 = (adj1 - 2) % 8;
	if (colorcmp(pix, adj[(adj1 + 2) % 8]) < colorcmp(pix, adj[(adj1 - 2) % 8]))
		adj2 = (adj1 + 2) % 8;
	if (colorcmp(adj[adj1], adj[adj2]) < 0.6)
		return (pix);
	return (two_colors_average(pix, \
			two_colors_average(adj[adj1], adj[adj2], 0.5), AA_MIX_RATIO));
}

static void		apply_aa(t_point p, t_rgb **pixdup)
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
	draw_px(GTKMGR.buf, p.x, p.y, new_color(pix, adj));
//	draw_px(GTKMGR.buf, p.x, p.y, color_average(adj, 8));
//	draw_px(GTKMGR.buf, p.x, p.y, two_colors_average(two_colors_average(pix, color_average(adj, 8), 0.5), pix, 0.5));
//	draw_px(GTKMGR.buf, p.x, p.y, ft_rgb(255, 0, 175, 0));
//	draw_px(GTKMGR.buf, p.x, p.y, pix);
}

static void		free_pixdup(t_rgb **pixdup)
{
	t_point		p;

	p.y = -1;
	while (++p.y < WIN_H)
		free(pixdup[p.y]);
	free(pixdup);
}

static void		antialiasing_core(void)
{
	t_point		p;
	int			aa[WIN_H][WIN_W];
	t_rgb		**pixdup;

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
			pixdup[p.y][p.x] = get_pixel(GTKMGR.buf, p.x, p.y);
			aa[p.y][p.x] = detect_edge(p);
//			if (aa[p.y][p.x] == 1)
//				ft_putendl("edge !");
//			draw_px(GTKMGR.buf, p.x, p.y, new_color);
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
				apply_aa(p, (t_rgb **)pixdup);
			}
		}
	}
	free_pixdup(pixdup);
}

void			antialiasing(void)
{
	int			i;

	i = -1;
	while (++i < AA_ITERATIONS)
		antialiasing_core();
}
