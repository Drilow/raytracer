/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:06:53 by adleau            #+#    #+#             */
/*   Updated: 2019/01/16 10:04:08 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#include <display/display.h>

extern t_global		g_global;

void					for_file(GtkWidget *button)
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

void					handle_cube_template(void)
{
	ADD_VIEW.cube = gtk_button_new();
	ADD_VIEW.cube_img = gtk_image_new_from_file("uiconfig/cube.png");
	gtk_widget_set_tooltip_text(ADD_VIEW.cube, "Cube");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cube), ADD_VIEW.cube_img);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.cube, 2, 6, 1, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.cube), "clicked", G_CALLBACK(add_cube),
	NULL);
}

void					for_template(void)
{
	handle_cube_template();
	ADD_VIEW.tetra = gtk_button_new();
	ADD_VIEW.tetra_img = gtk_image_new_from_file("uiconfig/tetra.png");
	gtk_widget_set_tooltip_text(ADD_VIEW.tetra, "Tetrahedron");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.tetra), ADD_VIEW.tetra_img);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.tetra, 3, 6, 1, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.tetra), "clicked", G_CALLBACK(add_tetra),
	NULL);
	ADD_VIEW.dode = gtk_button_new();
	ADD_VIEW.dode_img = gtk_image_new_from_file("uiconfig/dodecahedron.png");
	gtk_widget_set_tooltip_text(ADD_VIEW.dode, "Dodecahedron");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.dode), ADD_VIEW.dode_img);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.dode, 2, 7, 1, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.dode), "clicked", G_CALLBACK(add_dode),
	NULL);
	ADD_VIEW.pyramid = gtk_button_new();
	ADD_VIEW.pyramid_img = gtk_image_new_from_file("uiconfig/pyramid.png");
	gtk_widget_set_tooltip_text(ADD_VIEW.pyramid, "Pyramid");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.pyramid), ADD_VIEW.pyramid_img);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.pyramid, 3, 7, 1, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.pyramid),
	"clicked", G_CALLBACK(add_pyramid), NULL);
	gtk_widget_show_all(ADD_VIEW.win);
}

void					handle_radio_buttons(void)
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
	if (ADD_VIEW.saved_type / 10 != 6)
	{
		gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(ADD_VIEW.from_template), true);
		add_cube();
	}
}
