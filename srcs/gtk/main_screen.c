/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:18:24 by adleau            #+#    #+#             */
/*   Updated: 2019/01/16 10:57:07 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <unistd.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>

extern t_global g_global;

void				add_view(void)
{
	t_obj			*o;

	if (!(o = (t_obj*)malloc(sizeof(t_obj))))
		exit_properly(1);
	o->type = -5;
	o->enabled = true;
	edit_win(o, GTKMGR.ui.main_view.win);
}

void				handle_main_view(void)
{
	GTKMGR.ui.main_view.add_img
	= gtk_image_new_from_file("uiconfig/plus-sign-in-a-black-circle.png");
	GTKMGR.ui.main_view.filters_img
	= gtk_image_new_from_file("uiconfig/filter.png");
	GTKMGR.ui.main_view.select_img
	= gtk_image_new_from_file("uiconfig/new-file.png");
	GTKMGR.ui.main_view.export_img
	= gtk_image_new_from_file("uiconfig/scale-symbol.png");
	GTKMGR.ui.main_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.main_view.win),
	GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.main_view.win), "raytracer");
	GTKMGR.ui.main_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.win),
	GTKMGR.ui.main_view.grid);
	GTKMGR.ui.main_view.buttonbox
	= gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.grid),
	GTKMGR.ui.main_view.buttonbox);
	GTKMGR.ui.main_view.list_button = gtk_button_new();
	GTKMGR.ui.main_view.add_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.add_button, "add object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.add_button), "clicked",
	G_CALLBACK(add_view), NULL);
	handle_main_view_2();
}
