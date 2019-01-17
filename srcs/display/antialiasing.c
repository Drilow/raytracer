/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 22:52:03 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/16 22:04:22 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <display/display.h>
#include <global.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <objects/object.h>
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
}

static void		free_pixdup(t_rgb **pixdup)
{
	t_point		p;

	p.y = -1;
	while (++p.y < WIN_H)
	{
		free(pixdup[p.y]);
		pixdup[p.y] = NULL;
	}
	free(pixdup);
	pixdup = NULL;
}

static void		free_aa(int **aa)
{
	int i;

	i = -1;
	while (++i < WIN_H)
	{
		free(aa[i]);
		aa[i] = NULL;
	}
	free(aa);
	aa = NULL;
}

static void		antialiasing_core(void)
{
	t_point		p;
	int			**aa;//[WIN_H][WIN_W];
	t_rgb		**pixdup;

	p.y = -1;
	pixdup = NULL;
	aa = NULL;
	if (!(pixdup = (t_rgb **)malloc(sizeof(t_rgb *) * WIN_H)))
		ft_exit("malloc error", 0);
	if (!(aa = (int **)malloc(sizeof(int *) * WIN_H)))
		ft_exit("malloc error", 0);
	while (++p.y < WIN_H)
	{
		p.x = -1;
		pixdup[p.y] = NULL;
		aa[p.y] = NULL;
		if (!(pixdup[p.y] = (t_rgb *)malloc(sizeof(t_rgb) * WIN_W)))
			ft_exit("malloc error", 0);
		if (!(aa[p.y] = (int *)malloc(sizeof(int) * WIN_W)))
			ft_exit("malloc error", 0);
		while (++p.x < WIN_W)
		{
			pixdup[p.y][p.x] = get_pixel(GTKMGR.buf, p.x, p.y);
			aa[p.y][p.x] = detect_edge(p);
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
	free_aa(aa);
}

void			antialiasing(void)
{
	int			i;

	i = -1;
	while (++i < AA_ITERATIONS)
		antialiasing_core();
}
