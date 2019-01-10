/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_templates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:10:17 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 17:11:23 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global		g_global;

void				add_cube(void)
{
	deactivate_buttons_from_tp(ADD_VIEW.cube);
	gtk_widget_set_state_flags(ADD_VIEW.cube,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	if (ADD_VIEW.height_img)
	{
		gtk_widget_destroy(ADD_VIEW.height_img);
		gtk_widget_destroy(ADD_VIEW.height_spin);
		ADD_VIEW.height_img = NULL;
	}
	ADD_VIEW.sw.o->type = 66;
}

void				add_tetra(void)
{
	deactivate_buttons_from_tp(ADD_VIEW.tetra);
	gtk_widget_set_state_flags(ADD_VIEW.tetra,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	if (ADD_VIEW.height_img)
	{
		gtk_widget_destroy(ADD_VIEW.height_img);
		gtk_widget_destroy(ADD_VIEW.height_spin);
		ADD_VIEW.height_img = NULL;
	}
	ADD_VIEW.sw.o->type = 67;
}

void				add_dode(void)
{
	deactivate_buttons_from_tp(ADD_VIEW.dode);
	gtk_widget_set_state_flags(ADD_VIEW.dode,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	if (ADD_VIEW.height_img)
	{
		gtk_widget_destroy(ADD_VIEW.height_img);
		gtk_widget_destroy(ADD_VIEW.height_spin);
		ADD_VIEW.height_img = NULL;
	}
	ADD_VIEW.sw.o->type = 69;
}

void				add_height_spin(void)
{
	GtkAdjustment	*adj;

	ADD_VIEW.height_img = gtk_image_new_from_file("uiconfig/height.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.height_img, 0, 9, 1, 1);
	adj = gtk_adjustment_new(1, 0, 1000, .5, 1, 10);
	ADD_VIEW.height_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.height_spin, 1, 9, 3, 1);
	gtk_widget_show_all(ADD_VIEW.grid);
}

void				add_pyramid(void)
{
	deactivate_buttons_from_tp(ADD_VIEW.pyramid);
	gtk_widget_set_state_flags(ADD_VIEW.pyramid,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	add_height_spin();
	ADD_VIEW.sw.o->type = 68;
}
