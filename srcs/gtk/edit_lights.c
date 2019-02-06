/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:33:56 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:21:55 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				validate_light(t_light *l)
{
	GdkRGBA			*c;

	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit_properly(1);
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(g_global.r.gtk_mgr.ui.light_view.color), c);
	l->color.r = (unsigned char)(c->red * 255);
	l->color.g = (unsigned char)(c->green * 255);
	l->color.b = (unsigned char)(c->blue * 255);
	l->color.trans = ((unsigned char)255 - (c->alpha * 255));
	l->source.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.light_view.translate_x_spin));
	l->source.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.light_view.translate_y_spin));
	l->source.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.light_view.translate_z_spin));
	redraw(true);
	gtk_widget_destroy(GTK_WIDGET(g_global.r.gtk_mgr.ui.scene_view.win));
	scene_win();
}

void				handle_light_validation(t_light *l)
{
	int		r;

	r = gtk_dialog_run(GTK_DIALOG(g_global.r.gtk_mgr.ui.light_view.win));
	if (r == GTK_RESPONSE_ACCEPT)
	{
		validate_light(l);
		if (g_global.r.gtk_mgr.ui.light_view.win && GTK_IS_WIDGET(g_global.r.gtk_mgr.ui.light_view.win))
		{
			gtk_widget_destroy(GTK_WIDGET(g_global.r.gtk_mgr.ui.light_view.win));
			g_global.r.gtk_mgr.ui.light_view.win = NULL;
		}
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		redraw(false);
		gtk_widget_destroy(GTK_WIDGET(g_global.r.gtk_mgr.ui.light_view.win));
	}
}

void				attach_light_buttons(t_light *l)
{
	GtkAdjustment	*adj;

	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.light_view.grid),
	g_global.r.gtk_mgr.ui.light_view.translate_img, 0, 0, 1, 1);
	adj = gtk_adjustment_new(l->source.x, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.light_view.translate_x_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.light_view.grid),
	g_global.r.gtk_mgr.ui.light_view.translate_x_spin, 1, 0, 1, 1);
	adj = gtk_adjustment_new(l->source.y, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.light_view.translate_y_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.light_view.grid),
	g_global.r.gtk_mgr.ui.light_view.translate_y_spin, 2, 0, 1, 1);
	adj = gtk_adjustment_new(l->source.z, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.light_view.translate_z_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.light_view.grid),
	g_global.r.gtk_mgr.ui.light_view.translate_z_spin, 3, 0, 1, 1);
}

void				edit_light2(t_light *l)
{
	GdkRGBA			*c;

	attach_light_buttons(l);
	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit_properly(1);
	get_color_values(l->color, c);
	g_global.r.gtk_mgr.ui.light_view.color = gtk_color_chooser_widget_new();
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(g_global.r.gtk_mgr.ui.light_view.color), c);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.light_view.grid), g_global.r.gtk_mgr.ui.light_view.color, 0, 8, 4, 1);
	free(c);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.light_view.win);
	handle_light_validation(l);
}

void				edit_light(t_light *l, GtkWidget *parent)
{
	GtkWidget		*content_area;

	init_light_view();
	g_global.r.gtk_mgr.ui.light_view.translate_img = gtk_image_new_from_file("uiconfig/move.png");
	g_global.r.gtk_mgr.ui.light_view.win = gtk_dialog_new_with_buttons("Edit Light",
	GTK_WINDOW(parent),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
	"_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(g_global.r.gtk_mgr.ui.light_view.win),
	GTK_WINDOW(parent));
	gtk_window_set_position(GTK_WINDOW(g_global.r.gtk_mgr.ui.light_view.win), GTK_WIN_POS_MOUSE);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(g_global.r.gtk_mgr.ui.light_view.win));
	g_global.r.gtk_mgr.ui.light_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), g_global.r.gtk_mgr.ui.light_view.grid);
	edit_light2(l);
	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(
	GTK_DIALOG(g_global.r.gtk_mgr.ui.light_view.win), GTK_RESPONSE_ACCEPT));
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.light_view.win),
	"key-press-event", G_CALLBACK(on_key_press), NULL);
}
