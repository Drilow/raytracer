/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:02:31 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 12:32:18 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				handle_reflex_edit(t_obj *o)
{
	GtkAdjustment	*adj;

	ADD_VIEW.reflex_img = gtk_image_new_from_file("uiconfig/reflex.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.reflex_img,
	0, 8, 1, 1);
	adj = gtk_adjustment_new(o->reflex, 0, 255, 1, 1, 0);
	ADD_VIEW.reflex_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.reflex_spin,
	1, 8, 3, 1);
}

GtkAdjustment		*setup_adj(double n, int type)
{
	GtkAdjustment	*adj_mv;

	adj_mv = gtk_adjustment_new(0, -360, 360, .5, 1, 10);
	if (type == 6 || type / 10 == 6)
		adj_mv = gtk_adjustment_new(n * 360 / (2 * PI), -360, 360, .5, 1, 10);
	return (adj_mv);
}

void				attach_rotate(t_obj *o)
{
	GtkAdjustment	*adj_mv;

	ADD_VIEW.rotate_img = gtk_image_new_from_file("uiconfig/rotate.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.rotate_img,
	0, 11, 1, 1);
	adj_mv = setup_adj(((t_poly_obj*)o->obj)->rotation.x, o->type);
	ADD_VIEW.rotate_x_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.rotate_x_spin,
	1, 11, 1, 1);
	adj_mv = setup_adj(((t_poly_obj*)o->obj)->rotation.y, o->type);
	ADD_VIEW.rotate_y_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.rotate_y_spin,
	2, 11, 1, 1);
	adj_mv = setup_adj(((t_poly_obj*)o->obj)->rotation.z, o->type);
	ADD_VIEW.rotate_z_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.rotate_z_spin,
	3, 11, 1, 1);
}

void				attach_base_elens_edit(t_obj *o)
{
	GtkAdjustment	*adj_mv;

	ADD_VIEW.translate_img = gtk_image_new_from_file("uiconfig/move.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_img,
	0, 3, 1, 1);
	adj_mv = gtk_adjustment_new(o->position.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_x_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_x_spin,
	1, 3, 1, 1);
	adj_mv = gtk_adjustment_new(o->position.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_y_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_y_spin,
	2, 3, 1, 1);
	adj_mv = gtk_adjustment_new(o->position.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_z_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_z_spin,
	3, 3, 1, 1);
	attach_rotate(o);
}

void				handle_base_elems_edit(t_obj *o)
{
	GdkRGBA			*c;

	attach_base_elens_edit(o);
	handle_reflex_edit(o);
	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit_properly(1);
	get_color_values(o->color, c);
	ADD_VIEW.color = gtk_color_chooser_widget_new();
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.color, 0, 10, 4, 1);
	free(c);
}
