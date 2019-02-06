/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:28:27 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 16:00:10 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global g_global;

static gboolean		clicked(GtkWidget __attribute__((unused)) *widget,
							GdkEventButton *event)
{
	if (event->button == 1)
	{
		if (g_global.r.checker[(int)event->y][(int)event->x])
		{
			g_global.r.selected_obj = g_global.r.checker
			[(int)event->y][(int)event->x];
			if ((gtk_widget_get_state_flags(
			g_global.r.gtk_mgr.ui.main_view.select_button)
			& GTK_STATE_FLAG_CHECKED))
			{
				outline_obj(g_global.r.selected_obj);
				edit_win(g_global.r.selected_obj,
				g_global.r.gtk_mgr.ui.main_view.win);
			}
		}
	}
	return (true);
}

void				select_cb(void)
{
	if (!(gtk_widget_get_state_flags(
	g_global.r.gtk_mgr.ui.main_view.select_button) & GTK_STATE_FLAG_CHECKED))
	{
		gtk_widget_set_state_flags(
		g_global.r.gtk_mgr.ui.main_view.select_button,
		GTK_STATE_FLAG_CHECKED, false);
		g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.event_box),
		"button_press_event",
		G_CALLBACK(clicked),
		g_global.r.gtk_mgr.ui.main_view.render_area);
	}
	else
		gtk_widget_unset_state_flags(
		g_global.r.gtk_mgr.ui.main_view.select_button, GTK_STATE_FLAG_CHECKED);
}

void				handle_main_view_3(void)
{
	g_global.r.gtk_mgr.ui.main_view.export_button = gtk_button_new();
	gtk_button_set_image(
	GTK_BUTTON(g_global.r.gtk_mgr.ui.main_view.export_button),
	g_global.r.gtk_mgr.ui.main_view.export_img);
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.main_view.export_button,
	"export to png format");
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.export_button),
	"clicked", G_CALLBACK(export_view), NULL);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.main_view.buttonbox),
	g_global.r.gtk_mgr.ui.main_view.export_button);
	handle_drawing();
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.win),
	"key-press-event", G_CALLBACK(on_key_press), NULL);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.main_view.win);
	gtk_widget_destroy(g_global.base_view.win);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.win),
	"destroy", G_CALLBACK(handle_x_button), NULL);
}

void				handle_main_view_2(void)
{
	gtk_button_set_image(GTK_BUTTON(g_global.r.gtk_mgr.ui.main_view.add_button),
	g_global.r.gtk_mgr.ui.main_view.add_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.main_view.buttonbox),
	g_global.r.gtk_mgr.ui.main_view.add_button);
	g_global.r.gtk_mgr.ui.main_view.filters_button = gtk_button_new();
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.main_view.filters_button,
	"filters");
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.filters_button),
	"clicked", G_CALLBACK(filter_win), NULL);
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.main_view.filters_button),
	g_global.r.gtk_mgr.ui.main_view.filters_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.main_view.buttonbox),
	g_global.r.gtk_mgr.ui.main_view.filters_button);
	g_global.r.gtk_mgr.ui.main_view.select_button = gtk_button_new();
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.main_view.select_button,
	"select object");
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.select_button),
	"clicked", G_CALLBACK(select_cb), NULL);
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.main_view.select_button),
	g_global.r.gtk_mgr.ui.main_view.select_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.main_view.buttonbox),
	g_global.r.gtk_mgr.ui.main_view.select_button);
	handle_main_view_3();
}
