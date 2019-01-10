/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_handlers3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:07:24 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 17:09:14 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtk/gtk.h>
#include <geometry/geometry.h>

void				get_color_values(t_rgb col, GdkRGBA *c)
{
	c->red = (gdouble)(col.r) / 255;
	c->green = (gdouble)(col.g) / 255;
	c->blue = (gdouble)(col.b) / 255;
	c->alpha = (gdouble)(255 - col.trans) / 255;
}
