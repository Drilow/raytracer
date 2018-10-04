/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:18:24 by adleau            #+#    #+#             */
/*   Updated: 2018/10/04 17:35:38 by adleau           ###   ########.fr       */
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

static gboolean		clicked(GtkWidget __attribute__((unused))*widget, GdkEventButton *event)
{
	if (event->button == 1)
	{
		if (g_global.r->checker[(int)event->y][(int)event->x])
		{
			g_global.r->selected_obj = g_global.r->checker[(int)event->y][(int)event->x];
			if ((gtk_widget_get_state_flags(GTKMGR.ui.main_view.select_button) & GTK_STATE_FLAG_CHECKED))
			{
				outline_obj(g_global.r->selected_obj);
				edit_win(g_global.r->selected_obj);
			}
		}
	}
	return (true);
}

void				add_view(void)
{
	t_obj			*o;

	if (!(o = (t_obj*)malloc(sizeof(t_obj))))
		exit(1);
	o->type = -5;
	edit_win(o);
}

void				select_cb(void)
{
	if (!(gtk_widget_get_state_flags(GTKMGR.ui.main_view.select_button) & GTK_STATE_FLAG_CHECKED))
	{
		gtk_widget_set_state_flags(GTKMGR.ui.main_view.select_button, GTK_STATE_FLAG_CHECKED, false);
		g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.event_box),
						 "button_press_event",
						 G_CALLBACK(clicked),
						 GTKMGR.ui.main_view.render_area);
	}
	else
		gtk_widget_unset_state_flags(GTKMGR.ui.main_view.select_button, GTK_STATE_FLAG_CHECKED);
}

void				handle_main_view(void)
{
	GTKMGR.ui.main_view.add_img = gtk_image_new_from_file("uiconfig/plus-sign-in-a-black-circle.png");
	GTKMGR.ui.main_view.filters_img = gtk_image_new_from_file("uiconfig/filter.png");
	GTKMGR.ui.main_view.select_img = gtk_image_new_from_file("uiconfig/new-file.png");
	GTKMGR.ui.main_view.export_img = gtk_image_new_from_file("uiconfig/scale-symbol.png");
	GTKMGR.ui.main_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.main_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.main_view.win), "raytracer");
	GTKMGR.ui.main_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.win), GTKMGR.ui.main_view.grid);
	GTKMGR.ui.main_view.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.grid), GTKMGR.ui.main_view.buttonbox);
	GTKMGR.ui.main_view.add_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.add_button, "add object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.add_button), "clicked", G_CALLBACK(add_view), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.add_button), GTKMGR.ui.main_view.add_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.add_button);
	GTKMGR.ui.main_view.filters_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.filters_button, "filters");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.filters_button), "clicked", G_CALLBACK(filter_win), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.filters_button), GTKMGR.ui.main_view.filters_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.filters_button);
	GTKMGR.ui.main_view.select_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.select_button, "select object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.select_button), "clicked", G_CALLBACK(select_cb), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.select_button), GTKMGR.ui.main_view.select_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.select_button);
	GTKMGR.ui.main_view.export_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.export_button), GTKMGR.ui.main_view.export_img);
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.export_button, "export to png format");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.export_button), "clicked", G_CALLBACK(export_view), NULL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.export_button);
	handle_drawing();
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.win), "key-press-event", G_CALLBACK(on_key_press), NULL);
	gtk_widget_show_all(GTKMGR.ui.main_view.win);
	gtk_widget_destroy(g_global.base_view.win);
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.win), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

