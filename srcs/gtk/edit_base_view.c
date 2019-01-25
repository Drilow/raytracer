/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_base_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:17:37 by adleau            #+#    #+#             */
/*   Updated: 2019/01/25 14:04:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				edit_plane_view(t_plane *p)
{
	GtkAdjustment	*adj;

	deactivate_buttons(ADD_VIEW.plane_button);
	gtk_widget_set_state_flags(ADD_VIEW.plane_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.vector_img = gtk_image_new_from_file("uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_img, 0, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_x, 1, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_y, 2, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_z, 3, 1, 1, 1);
}

void				end_cone_view(t_cone *c)
{
	GtkAdjustment	*adj_angle;

	adj_angle = gtk_adjustment_new(c->angle * 360, 0, 360, 1, 1, 10);
	ADD_VIEW.angle_spin = gtk_spin_button_new(adj_angle, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.angle_spin, 1, 6, 1, 1);
}

void				edit_cone_view(t_cone *c)
{
	GtkAdjustment	*adj;

	deactivate_buttons(ADD_VIEW.cone_button);
	gtk_widget_set_state_flags(ADD_VIEW.cone_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.vector_img = gtk_image_new_from_file("uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_img, 0, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_x, 1, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_y, 2, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_z, 3, 4, 1, 1);
	ADD_VIEW.inf_img = gtk_image_new_from_file("uiconfig/infinite.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.inf_img, 0, 5, 1, 1);
	ADD_VIEW.infinite = gtk_switch_new();
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.infinite, 1, 5, 1, 1);
	gtk_switch_set_state(GTK_SWITCH(ADD_VIEW.infinite), c->infinite);
	ADD_VIEW.angle_img = gtk_image_new_from_file("uiconfig/angle.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.angle_img, 0, 6, 1, 1);
	end_cone_view(c);
}

void				handle_switch(t_cylinder *c)
{
	ADD_VIEW.infinite = gtk_switch_new();
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.infinite, 1, 5, 1, 1);
	gtk_switch_set_state(GTK_SWITCH(ADD_VIEW.infinite), c->infinite);
}

void				edit_cylinder_view(t_cylinder *c)
{
	GtkAdjustment	*adj_scale;
	GtkAdjustment	*adj;

	deactivate_buttons(ADD_VIEW.cylinder_button);
	gtk_widget_set_state_flags(ADD_VIEW.cylinder_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(c->radius, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_spin, 1, 1, 3, 1);
	ADD_VIEW.vector_img = gtk_image_new_from_file("uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_img, 0, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_x, 1, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_y, 2, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_z, 3, 4, 1, 1);
	ADD_VIEW.inf_img = gtk_image_new_from_file("uiconfig/infinite.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.inf_img, 0, 5, 1, 1);
	handle_switch(c);
}
