/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outline_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:36:15 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:11:30 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <extra/extra_defs.h>
#include <display/display.h>

extern t_global		g_global;

void				outline_algo(t_obj *o, int x, int y)
{
	if (g_global.r.checker[y][x] == o)
	{
		if (y - 1 >= 0 && g_global.r.checker[y - 1][x] != o)
		{
			draw_px(g_global.r.gtk_mgr.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(g_global.r.gtk_mgr.buf, x, y - 1, ft_rgb(255, 0, 0, 0));
		}
		if (y + 1 < WIN_H && g_global.r.checker[y + 1][x] != o)
		{
			draw_px(g_global.r.gtk_mgr.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(g_global.r.gtk_mgr.buf, x, y + 1, ft_rgb(255, 0, 0, 0));
		}
		if (x - 1 >= 0 && g_global.r.checker[y][x - 1] != o)
		{
			draw_px(g_global.r.gtk_mgr.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(g_global.r.gtk_mgr.buf, x - 1, y, ft_rgb(255, 0, 0, 0));
		}
		if (x + 1 < WIN_W && g_global.r.checker[y][x + 1] != o)
		{
			draw_px(g_global.r.gtk_mgr.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(g_global.r.gtk_mgr.buf, x + 1, y, ft_rgb(255, 0, 0, 0));
		}
	}
}

void				end_outline(void)
{
	if (g_global.r.gtk_mgr.pixmap)
		cairo_surface_destroy(g_global.r.gtk_mgr.pixmap);
	g_global.r.gtk_mgr.pixmap = cairo_image_surface_create_for_data(
	g_global.r.gtk_mgr.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H,
	cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(g_global.r.gtk_mgr.pixmap) != CAIRO_STATUS_SUCCESS)
		exit_properly(1);
	cairo_surface_mark_dirty(g_global.r.gtk_mgr.pixmap);
	gtk_image_set_from_surface(GTK_IMAGE(
	g_global.r.gtk_mgr.ui.main_view.render_area), g_global.r.gtk_mgr.pixmap);
}

void				outline_obj(t_obj *o)
{
	int				x;
	int				y;

	y = -1;
	if ((g_global.r.gtk_mgr.saved))
	{
		free(g_global.r.gtk_mgr.saved);
		g_global.r.gtk_mgr.saved = NULL;
	}
	if (!(g_global.r.gtk_mgr.saved = ft_ustrdup(g_global.r.gtk_mgr.buf,
	WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
		exit_properly(1);
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			outline_algo(o, x, y);
	}
	end_outline();
}
