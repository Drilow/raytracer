/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:50:07 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/05 18:18:41 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <display/display.h>
#include <global.h>
#include <gtk/gtk.h>
#include <extra/extra_defs.h>

extern t_global	g_global;

t_rgb			two_colors_average(t_rgb a, t_rgb b, double ratio)
{
	return (ft_rgb((a.r * ratio) + (b.r * (1 - ratio)), \
					(a.g * ratio) + (b.g * (1 - ratio)), \
					(a.b * ratio) + (b.b * (1 - ratio)), \
					(a.trans * ratio) + (b.trans * (1 - ratio))));
}

double			colorcmp(t_rgb a, t_rgb b)
{
	t_rpoint	cmp;
	double		clr_cmp;
	double		brightness_cmp;

	cmp.x = 1 - ((double)ft_abs(a.r - b.r) / 255);
	cmp.y = 1 - ((double)ft_abs(a.g - b.g) / 255);
	cmp.z = 1 - ((double)ft_abs(a.b - b.b) / 255);
	clr_cmp = (cmp.x + cmp.y + cmp.z) / 3;
	brightness_cmp = 1 - \
		((double)ft_abs(a.r + a.g + a.b - b.r - b.g - b.b) / 765);
	return (clr_cmp * 0.80 + brightness_cmp * 0.20);
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

static void		apply_aa_core(t_point p, t_rgb **pixdup, t_rgb *adj)
{
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
}

void			apply_aa(t_point p, t_rgb **pixdup)
{
	t_rgb		pix;
	t_rgb		*adj;
	int			i;

	pix = pixdup[p.y][p.x];
	if (!(adj = (t_rgb *)malloc(sizeof(t_rgb) * 8)))
		ft_exit("Malloc error ('antialiasing_2.c' --> Ln 97)", 1);
	i = -1;
	while (++i < 8)
		adj[i] = pixdup[p.y][p.x];
	apply_aa_core(p, pixdup, adj);
	draw_px(GTKMGR.buf, p.x, p.y, new_color(pix, adj));
	free(adj);
	adj = NULL;
}
