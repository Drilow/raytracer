/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:18:24 by adleau            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/10/22 12:21:45 by Dagnear          ###   ########.fr       */
=======
/*   Updated: 2018/10/20 11:46:58 by adleau           ###   ########.fr       */
>>>>>>> 99c9d7ab43d8b2b0a01a1df3b5095e745df703aa
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <unistd.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global g_global;

void				add_view(void)
{
	t_obj			*o;

	if (!(o = (t_obj*)malloc(sizeof(t_obj))))
		exit(1); // to fix
	o->type = -5;
	edit_win(o);
}

void				handle_main_view(void)
{
	GTKMGR.ui.main_view.add_img =
	gtk_image_new_from_file("uiconfig/plus-sign-in-a-black-circle.png");
	GTKMGR.ui.main_view.filters_img =
	gtk_image_new_from_file("uiconfig/filter.png");
	GTKMGR.ui.main_view.select_img =
	gtk_image_new_from_file("uiconfig/new-file.png");
	GTKMGR.ui.main_view.export_img =
	gtk_image_new_from_file("uiconfig/scale-symbol.png");
	GTKMGR.ui.main_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.main_view.win),
	GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.main_view.win), "raytracer");
	GTKMGR.ui.main_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.win),
	GTKMGR.ui.main_view.grid);
	GTKMGR.ui.main_view.buttonbox =
	gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.grid),
	GTKMGR.ui.main_view.buttonbox);
	GTKMGR.ui.main_view.list_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.list_button, "list object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.list_button), "clicked", G_CALLBACK(scene_win), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.list_button), GTKMGR.ui.main_view.add_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.list_button);
	GTKMGR.ui.main_view.add_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.add_button, "add object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.add_button), "clicked",
	G_CALLBACK(add_view), NULL);
	handle_main_view_2();
}
