/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:50:02 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/22 21:06:11 by alacrois         ###   ########.fr       */
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

void				free_pixdup(t_rgb **pixdup)
{
	t_point			p;

	p.y = -1;
	while (++p.y < WIN_H)
	{
		free(pixdup[p.y]);
		pixdup[p.y] = NULL;
	}
	free(pixdup);
	pixdup = NULL;
}

void				free_aa(int **aa)
{
	int				i;

	i = -1;
	while (++i < WIN_H)
	{
		free(aa[i]);
		aa[i] = NULL;
	}
	free(aa);
	aa = NULL;
}

t_rgb				get_pixel(unsigned char *buf, int x, int y)
{
	unsigned char	*ptr;
	t_rgb			px;
	int				stride;
	int				bpp;

	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	bpp = stride / WIN_W;
	ptr = buf + (y * stride) + x * bpp;
	px.r = ptr[2];
	px.g = ptr[1];
	px.b = ptr[0];
	px.trans = 0;
	return (px);
}
