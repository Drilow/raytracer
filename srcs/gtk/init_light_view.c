/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:59:22 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 17:06:17 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				init_filter_img(void)
{
	FILTER_VIEW.bw_img = gtk_image_new_from_file("uiconfig/bw.png");
	FILTER_VIEW.sepia_img = gtk_image_new_from_file("uiconfig/sepia.png");
	FILTER_VIEW.reversed_img = gtk_image_new_from_file("uiconfig/reversed.png");
}

void				init_light_view(void)
{
	LIGHT_VIEW.win = NULL;
	LIGHT_VIEW.grid = NULL;
	LIGHT_VIEW.x_label = NULL;
	LIGHT_VIEW.y_label = NULL;
	LIGHT_VIEW.z_label = NULL;
	LIGHT_VIEW.translate_img = NULL;
	LIGHT_VIEW.translate_x_spin = NULL;
	LIGHT_VIEW.translate_y_spin = NULL;
	LIGHT_VIEW.translate_z_spin = NULL;
	LIGHT_VIEW.color = NULL;
}
