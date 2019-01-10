/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 22:16:44 by adleau            #+#    #+#             */
/*   Updated: 2018/09/12 08:13:14 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <gtk/gtk.h>

extern t_global		g_global;

void				draw_px(unsigned char *buf, int x, int y, t_rgb cols)
{
	unsigned char	*ptr;
	int				stride;

	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	ptr = buf + (y * stride) + x * 4;
	ptr[2] = cols.r;
	ptr[1] = cols.g;
	ptr[0] = cols.b;
}
