/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:50:09 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/06 14:23:18 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <display/display.h>
#include <global.h>

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

	pix = get_pixel(g_global.r.gtk_mgr.buf, p.x, p.y);
	i = -1;
	while (++i < 4)
		adjacent[i] = pix;
	if (p.y > 0)
		adjacent[0] = get_pixel(g_global.r.gtk_mgr.buf, p.x, p.y - 1);
	if (p.x + 1 < WIN_W)
		adjacent[1] = get_pixel(g_global.r.gtk_mgr.buf, p.x + 1, p.y);
	if (p.y + 1 < WIN_H)
		adjacent[1] = get_pixel(g_global.r.gtk_mgr.buf, p.x, p.y + 1);
	if (p.x > 0)
		adjacent[3] = get_pixel(g_global.r.gtk_mgr.buf, p.x - 1, p.y);
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
			ft_exit("Malloc error ('antialiasing_1.c' --> Ln 77)", 1);
		if (!(aa[p.y] = (int *)malloc(sizeof(int) * WIN_W)))
			ft_exit("Malloc error ('antialiasing_1.c' --> Ln 79)", 1);
		while (++p.x < WIN_W)
		{
			pixdup[p.y][p.x] = get_pixel(g_global.r.gtk_mgr.buf, p.x, p.y);
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
		ft_exit("Malloc error ('antialiasing_1.c' --> Ln 97)", 1);
	if (!(aa = (int **)malloc(sizeof(int *) * WIN_H)))
		ft_exit("Malloc error ('antialiasing_1.c' --> Ln 99)", 1);
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
