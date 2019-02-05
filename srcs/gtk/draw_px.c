/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_px.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 22:16:44 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 15:31:02 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				draw_px(unsigned char *buf, int x, int y, t_rgb cols)
{
	unsigned char	*ptr;
	int				stride;
	int				bpp;

	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	bpp = stride / WIN_W;
	ptr = buf + (y * stride) + x * bpp;
	ptr[2] = cols.r;
	ptr[1] = cols.g;
	ptr[0] = cols.b;
}
