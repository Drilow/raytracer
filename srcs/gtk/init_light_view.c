/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:59:22 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:56:33 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

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
