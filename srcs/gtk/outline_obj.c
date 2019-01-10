/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outline_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:36:15 by adleau            #+#    #+#             */
/*   Updated: 2019/01/03 04:30:09 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>

extern t_global		g_global;

void				outline_algo(t_obj *o, int x, int y)
{
	if (g_global.r->checker[y][x] == o)
	{
		if (y - 1 >= 0 && g_global.r->checker[y - 1][x] != o)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x, y - 1, ft_rgb(255, 0, 0, 0));
		}
		if (y + 1 < WIN_H && g_global.r->checker[y + 1][x] != o)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x, y + 1, ft_rgb(255, 0, 0, 0));
		}
		if (x - 1 >= 0 && g_global.r->checker[y][x - 1] != o)
		{
			draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
			draw_px(GTKMGR.buf, x - 1, y, ft_rgb(255, 0, 0, 0));
		}
		if (x + 1 < WIN_W && g_global.r->checker[y][x + 1] != o)
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
	if (!(GTKMGR.saved = ft_ustrdup(GTKMGR.buf,
	WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
		exit(1); //to fix
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
		exit(1); // to fix
	cairo_surface_mark_dirty(PIXMAP);
	gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area),
	PIXMAP);
}
