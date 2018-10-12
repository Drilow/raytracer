/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outline_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:36:15 by adleau            #+#    #+#             */
/*   Updated: 2018/10/12 15:45:05 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global		g_global;

void				outline_algo(t_obj *o, int x, int y)
{
	if (g_global.r->checker[y][x] == o)
	{
		if (g_global.r->checker[y - 1][x] != o && y - 1 >= 0)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x, y - 1, ft_rgb(255, 0, 0, 0));
		}
		if (g_global.r->checker[y + 1][x] != o && y + 1 < WIN_H)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x, y + 1, ft_rgb(255, 0, 0, 0));
		}
		if (g_global.r->checker[y][x - 1] != o && x - 1 >= 0)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x - 1, y, ft_rgb(255, 0, 0, 0));
		}
		if (g_global.r->checker[y][x + 1] != o && x + 1 < WIN_W)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x + 1, y, ft_rgb(255, 0, 0, 0));
		}
	}
}

void				outline_obj(t_obj *o)
{
	int				x;
	int				y;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			outline_algo(o, x, y);
	}
	if (PIXMAP)
		cairo_surface_destroy(PIXMAP);
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf,
	CAIRO_FORMAT_RGB24, WIN_W, WIN_H,
	cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit(1);
	cairo_surface_mark_dirty(PIXMAP);
	gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area),
	PIXMAP);
}
