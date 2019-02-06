/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:22:54 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:10:01 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				edit_sphere_view(t_sphere *s)
{
	GtkAdjustment	*adj_scale;

	deactivate_buttons(g_global.r.gtk_mgr.ui.add_view.sphere_button);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.sphere_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	g_global.r.gtk_mgr.ui.add_view.scale_img =
		gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(s->radius, 0, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.scale_spin =
		gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.scale_spin, 1, 1, 3, 1);
}
