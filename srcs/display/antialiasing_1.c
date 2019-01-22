/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:50:09 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/22 21:48:46 by alacrois         ###   ########.fr       */
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

static int		detect_edge_core(t_rgb *adjacent, t_rgb pix)
{
	if (colorcmp(adjacent[0], adjacent[1]) > AA_UPPER_THRESHOLD \
		&& colorcmp(pix, two_colors_average(adjacent[0], adjacent[1], 0.5)) \
		< AA_LOWER_THRESHOLD)
		return (1);
	if (colorcmp(adjacent[1], adjacent[2]) > AA_UPPER_THRESHOLD \
		&& colorcmp(pix, two_colors_average(adjacent[1], adjacent[2], 0.5)) \
		< AA_LOWER_THRESHOLD)
		return (1);
	if (colorcmp(adjacent[2], adjacent[3]) > AA_UPPER_THRESHOLD \
		&& colorcmp(pix, two_colors_average(adjacent[2], adjacent[3], 0.5)) \
		< AA_LOWER_THRESHOLD)
		return (1);
	if (colorcmp(adjacent[3], adjacent[0]) > AA_UPPER_THRESHOLD \
		&& colorcmp(pix, two_colors_average(adjacent[3], adjacent[0], 0.5)) \
		< AA_LOWER_THRESHOLD)
		return (1);
	return (0);
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
	return (detect_edge_core(adjacent, pix));
}

static void		antialiasing_core_2(int **aa, t_rgb **pixdup)
{
	t_point		p;

	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		pixdup[p.y] = NULL;
		aa[p.y] = NULL;
		if (!(pixdup[p.y] = (t_rgb *)malloc(sizeof(t_rgb) * WIN_W)))
			exit_properly(1);
		if (!(aa[p.y] = (int *)malloc(sizeof(int) * WIN_W)))
			exit_properly(1);
		while (++p.x < WIN_W)
		{
			pixdup[p.y][p.x] = get_pixel(GTKMGR.buf, p.x, p.y);
			aa[p.y][p.x] = detect_edge(p);
		}
	}
}

static void		antialiasing_core(void)
{
	t_point		p;
	int			**aa;
	t_rgb		**pixdup;

	pixdup = NULL;
	aa = NULL;
	if (!(pixdup = (t_rgb **)malloc(sizeof(t_rgb *) * WIN_H)))
		exit_properly(1);
	if (!(aa = (int **)malloc(sizeof(int *) * WIN_H)))
		exit_properly(1);
	antialiasing_core_2(aa, pixdup);
	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			if (aa[p.y][p.x] == 1)
				apply_aa(p, (t_rgb **)pixdup);
		}
	}
	free_pixdup(pixdup);
	free_aa(aa);
}

void			antialiasing(void)
{
	int			i;

	i = -1;
	if (ANTIALIASING == 0)
		return ;
	while (++i < AA_ITERATIONS)
		antialiasing_core();
}
