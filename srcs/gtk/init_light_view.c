/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:59:22 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:22:10 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				init_filter_img(void)
{
	g_global.r.gtk_mgr.ui.filter_view.bw_img
	= gtk_image_new_from_file("uiconfig/bw.png");
	g_global.r.gtk_mgr.ui.filter_view.sepia_img
	= gtk_image_new_from_file("uiconfig/sepia.png");
	g_global.r.gtk_mgr.ui.filter_view.reversed_img
	= gtk_image_new_from_file("uiconfig/reversed.png");
}

void				init_light_view(void)
{
	g_global.r.gtk_mgr.ui.light_view.win = NULL;
	g_global.r.gtk_mgr.ui.light_view.grid = NULL;
	g_global.r.gtk_mgr.ui.light_view.x_label = NULL;
	g_global.r.gtk_mgr.ui.light_view.y_label = NULL;
	g_global.r.gtk_mgr.ui.light_view.z_label = NULL;
	g_global.r.gtk_mgr.ui.light_view.translate_img = NULL;
	g_global.r.gtk_mgr.ui.light_view.translate_x_spin = NULL;
	g_global.r.gtk_mgr.ui.light_view.translate_y_spin = NULL;
	g_global.r.gtk_mgr.ui.light_view.translate_z_spin = NULL;
	g_global.r.gtk_mgr.ui.light_view.color = NULL;
}
