/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_templates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:10:17 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 18:21:25 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				add_cube(void)
{
	deactivate_buttons_from_tp(g_global.r.gtk_mgr.ui.add_view.cube);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.cube,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	if (g_global.r.gtk_mgr.ui.add_view.height_img)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_img);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_spin);
		g_global.r.gtk_mgr.ui.add_view.height_img = NULL;
	}
	g_global.r.gtk_mgr.ui.add_view.sw.o->type = 66;
}

void				add_tetra(void)
{
	deactivate_buttons_from_tp(g_global.r.gtk_mgr.ui.add_view.tetra);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.tetra,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	if (g_global.r.gtk_mgr.ui.add_view.height_img)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_img);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_spin);
		g_global.r.gtk_mgr.ui.add_view.height_img = NULL;
	}
	g_global.r.gtk_mgr.ui.add_view.sw.o->type = 67;
}

void				add_dode(void)
{
	deactivate_buttons_from_tp(g_global.r.gtk_mgr.ui.add_view.dode);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.dode,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	if (g_global.r.gtk_mgr.ui.add_view.height_img)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_img);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_spin);
		g_global.r.gtk_mgr.ui.add_view.height_img = NULL;
	}
	g_global.r.gtk_mgr.ui.add_view.sw.o->type = 69;
}

void				add_height_spin(void)
{
	GtkAdjustment	*adj;

	g_global.r.gtk_mgr.ui.add_view.height_img = gtk_image_new_from_file(
		"uiconfig/height.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
		g_global.r.gtk_mgr.ui.add_view.height_img, 0, 9, 1, 1);
	adj = gtk_adjustment_new(1, 0, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.height_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
		g_global.r.gtk_mgr.ui.add_view.height_spin, 1, 9, 3, 1);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.add_view.grid);
}

void				add_pyramid(void)
{
	deactivate_buttons_from_tp(g_global.r.gtk_mgr.ui.add_view.pyramid);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.pyramid,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	add_height_spin();
	g_global.r.gtk_mgr.ui.add_view.sw.o->type = 68;
}
