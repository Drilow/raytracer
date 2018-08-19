/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 22:16:44 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 15:32:36 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <gtk/gtk.h>
#define PIXMAP g_global.gtk_mgr.pixmap

extern t_global		g_global;

void				draw_px(unsigned char *buf, int x, int y, t_rgb cols)
{
	unsigned char	*ptr;
	int				stride;

	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	ptr = buf + (y * stride) + x * 4;
	ptr[0] = cols.r;
	ptr[1] = cols.g;
	ptr[2] = cols.b;
}
