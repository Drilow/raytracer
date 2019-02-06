/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_handlers3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:07:24 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:00:50 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <gtk/gtk.h>
#include <geometry/geometry.h>

extern t_global			g_global;

void					for_template2(void)
{
	g_global.r.gtk_mgr.ui.add_view.pyramid = gtk_button_new();
	g_global.r.gtk_mgr.ui.add_view.pyramid_img = gtk_image_new_from_file(
	"uiconfig/pyramid.png");
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.pyramid,
	"Pyramid");
	gtk_button_set_image(GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.pyramid),
	g_global.r.gtk_mgr.ui.add_view.pyramid_img);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.pyramid, 3, 7, 1, 1);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.pyramid),
	"clicked", G_CALLBACK(add_pyramid), NULL);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.add_view.win);
}

void					for_template(void)
{
	handle_cube_template();
	g_global.r.gtk_mgr.ui.add_view.tetra = gtk_button_new();
	g_global.r.gtk_mgr.ui.add_view.tetra_img = gtk_image_new_from_file(
	"uiconfig/tetra.png");
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.tetra,
	"Tetrahedron");
	gtk_button_set_image(GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.tetra),
	g_global.r.gtk_mgr.ui.add_view.tetra_img);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.tetra, 3, 6, 1, 1);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.tetra),
	"clicked", G_CALLBACK(add_tetra),
	NULL);
	g_global.r.gtk_mgr.ui.add_view.dode = gtk_button_new();
	g_global.r.gtk_mgr.ui.add_view.dode_img = gtk_image_new_from_file(
	"uiconfig/dodecahedron.png");
	gtk_widget_set_tooltip_text(
	g_global.r.gtk_mgr.ui.add_view.dode, "Dodecahedron");
	gtk_button_set_image(GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.dode),
	g_global.r.gtk_mgr.ui.add_view.dode_img);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.dode, 2, 7, 1, 1);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.dode),
	"clicked", G_CALLBACK(add_dode), NULL);
	for_template2();
}

void				init_scene_view2(GtkCellRenderer *render)
{
	g_object_set(G_OBJECT(render), "foreground", "red", NULL);
	append_column_with_text(
	g_global.r.gtk_mgr.ui.scene_view.tree, "Type", render, TYPE_COLUMN);
	render = gtk_cell_renderer_text_new();
	g_object_set(render, "weight", PANGO_WEIGHT_BOLD, "weight-set",
	TRUE, NULL);
	append_column_with_text(
	g_global.r.gtk_mgr.ui.scene_view.tree, "Pos X", render, POS_X_COLUMN);
	append_column_with_text(
	g_global.r.gtk_mgr.ui.scene_view.tree, "Pos Y", render, POS_Y_COLUMN);
	append_column_with_text(
	g_global.r.gtk_mgr.ui.scene_view.tree, "Pos Z", render, POS_Z_COLUMN);
}

void				get_color_values(t_rgb col, GdkRGBA *c)
{
	c->red = (gdouble)(col.r) / 255;
	c->green = (gdouble)(col.g) / 255;
	c->blue = (gdouble)(col.b) / 255;
	c->alpha = (gdouble)(255 - col.trans) / 255;
}

gboolean			is_obj(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4 || type == 6
			|| type == 66 || type == 67 || type == 68 || type == 69)
		return (TRUE);
	return (FALSE);
}
