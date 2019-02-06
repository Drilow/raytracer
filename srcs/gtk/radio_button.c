/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:06:53 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:00:38 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void					for_file(GtkWidget *button)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
	{
		g_global.r.gtk_mgr.ui.add_view.file_opener =
		gtk_button_new_from_icon_name("document-open", GTK_ICON_SIZE_BUTTON);
		gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.file_opener,
		"Open obj File");
		gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
		g_global.r.gtk_mgr.ui.add_view.file_opener, 2, 7, 1, 1);
		g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.file_opener),
		"clicked", G_CALLBACK(open_poly_obj), NULL);
		gtk_widget_show_all(g_global.r.gtk_mgr.ui.add_view.win);
		g_global.r.gtk_mgr.ui.add_view.sw.o->type = 6;
	}
	else
	{
		if (g_global.r.gtk_mgr.ui.add_view.file_opener)
		{
			gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.file_opener);
			g_global.r.gtk_mgr.ui.add_view.file_opener = NULL;
		}
	}
}

void					handle_cube_template(void)
{
	g_global.r.gtk_mgr.ui.add_view.cube = gtk_button_new();
	g_global.r.gtk_mgr.ui.add_view.cube_img = gtk_image_new_from_file(
	"uiconfig/cube.png");
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.cube, "Cube");
	gtk_button_set_image(GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.cube),
	g_global.r.gtk_mgr.ui.add_view.cube_img);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.cube, 2, 6, 1, 1);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.cube),
	"clicked", G_CALLBACK(add_cube), NULL);
}

void					handle_other_buttons(void)
{
	if (g_global.r.gtk_mgr.ui.add_view.saved_type / 10 != 6
	&& g_global.r.gtk_mgr.ui.add_view.saved_type != 6)
	{
		gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(g_global.r.gtk_mgr.ui.add_view.from_template), true);
		add_cube();
	}
}

void					handle_radio_buttons(void)
{
	g_global.r.gtk_mgr.ui.add_view.same = gtk_radio_button_new_with_label(
	NULL, "Current object");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.same, 0, 5, 2, 1);
	g_global.r.gtk_mgr.ui.add_view.from_template =
	gtk_radio_button_new_with_label(NULL, "From Template");
	gtk_radio_button_join_group(GTK_RADIO_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.from_template),
	GTK_RADIO_BUTTON(g_global.r.gtk_mgr.ui.add_view.same));
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.from_template, 0, 6, 2, 1);
	g_global.r.gtk_mgr.ui.add_view.file_check = gtk_radio_button_new_with_label(
	NULL, "From File");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.file_check, 0, 7, 2, 1);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.file_check),
	"toggled", G_CALLBACK(radio_toggle), NULL);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.same), "toggled",
	G_CALLBACK(radio_toggle), NULL);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.from_template),
	"toggled", G_CALLBACK(radio_toggle), NULL);
	gtk_radio_button_join_group(
	GTK_RADIO_BUTTON(g_global.r.gtk_mgr.ui.add_view.file_check),
	GTK_RADIO_BUTTON(g_global.r.gtk_mgr.ui.add_view.same));
	handle_other_buttons();
}
