/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:06:53 by adleau            #+#    #+#             */
/*   Updated: 2018/10/04 18:08:03 by adleau           ###   ########.fr       */
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

static void			for_file(GtkWidget *button)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
	{
		ADD_VIEW.file_opener =
		gtk_button_new_from_icon_name("document-open", GTK_ICON_SIZE_BUTTON);
		gtk_widget_set_tooltip_text(ADD_VIEW.file_opener, "Open obj File");
		gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.file_opener,
		2, 7, 1, 1);
		g_signal_connect(G_OBJECT(ADD_VIEW.file_opener), "clicked",
		G_CALLBACK(open_poly_obj), NULL);
		gtk_widget_show_all(ADD_VIEW.win);
	}
	else
	{
		if (ADD_VIEW.file_opener)
		{
			gtk_widget_destroy(ADD_VIEW.file_opener);
			ADD_VIEW.file_opener = NULL;
		}
	}
}

static void			for_template(void)
{
	ADD_VIEW.cube = gtk_button_new();
	ADD_VIEW.cube_img = gtk_image_new_from_file("uiconfig/cube.png");
	gtk_widget_set_tooltip_text(ADD_VIEW.cube, "Cube");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cube), ADD_VIEW.cube_img);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.cube, 2, 6, 1, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.cube), "clicked", G_CALLBACK(add_cube),
	NULL);
	ADD_VIEW.tetra = gtk_button_new();
	ADD_VIEW.tetra_img = gtk_image_new_from_file("uiconfig/tetra.png");
	gtk_widget_set_tooltip_text(ADD_VIEW.tetra, "Tetrahedron");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.tetra), ADD_VIEW.tetra_img);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.tetra, 3, 6, 1, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.tetra), "clicked", G_CALLBACK(add_tetra),
	NULL);
	gtk_widget_show_all(ADD_VIEW.win);
}

static void			radio_toggle(GtkWidget *button)
{
	if (button == ADD_VIEW.file_check)
		for_file(button);
	if (button == ADD_VIEW.from_template)
	{
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
			for_template();
		else
		{
			if (ADD_VIEW.cube)
			{
				gtk_widget_destroy(ADD_VIEW.cube);
				ADD_VIEW.cube = NULL;
			}
			if (ADD_VIEW.tetra)
			{
				gtk_widget_destroy(ADD_VIEW.tetra);
				ADD_VIEW.tetra = NULL;
			}
		}
	}
}

void				handle_radio_buttons(void)
{
	ADD_VIEW.same = gtk_radio_button_new_with_label(NULL, "Current object");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.same, 0, 5, 2, 1);
	ADD_VIEW.from_template =
	gtk_radio_button_new_with_label(NULL, "From Template");
	gtk_radio_button_join_group(GTK_RADIO_BUTTON(ADD_VIEW.from_template),
	GTK_RADIO_BUTTON(ADD_VIEW.same));
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid),
	ADD_VIEW.from_template, 0, 6, 2, 1);
	ADD_VIEW.file_check = gtk_radio_button_new_with_label(NULL, "From File");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.file_check, 0, 7, 2, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.file_check),
	"toggled", G_CALLBACK(radio_toggle), NULL);
	g_signal_connect(G_OBJECT(ADD_VIEW.same), "toggled",
	G_CALLBACK(radio_toggle), NULL);
	g_signal_connect(G_OBJECT(ADD_VIEW.from_template),
	"toggled", G_CALLBACK(radio_toggle), NULL);
	gtk_radio_button_join_group(GTK_RADIO_BUTTON(ADD_VIEW.file_check),
	GTK_RADIO_BUTTON(ADD_VIEW.same));
}