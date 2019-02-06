/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_base_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:17:37 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:43:28 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				edit_plane_view(t_plane *p)
{
	GtkAdjustment	*adj;

	deactivate_buttons(g_global.r.gtk_mgr.ui.add_view.plane_button);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.plane_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	g_global.r.gtk_mgr.ui.add_view.vector_img = gtk_image_new_from_file(
	"uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_img, 0, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.x, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_x, 1, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.y, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_y, 2, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.z, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_z, 3, 1, 1, 1);
}

void				end_cone_view(t_cone *c)
{
	GtkAdjustment	*adj_angle;

	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.inf_img, 0, 5, 1, 1);
	g_global.r.gtk_mgr.ui.add_view.infinite = gtk_switch_new();
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.infinite, 1, 5, 1, 1);
	gtk_switch_set_state(GTK_SWITCH(g_global.r.gtk_mgr.ui.add_view.infinite),
	c->infinite);
	g_global.r.gtk_mgr.ui.add_view.angle_img = gtk_image_new_from_file(
	"uiconfig/angle.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.angle_img, 0, 6, 1, 1);
	adj_angle = gtk_adjustment_new(c->angle * 360, 0, 360, 1, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.angle_spin = gtk_spin_button_new(
	adj_angle, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.angle_spin, 1, 6, 1, 1);
}

void				edit_cone_view(t_cone *c)
{
	GtkAdjustment	*adj;

	deactivate_buttons(g_global.r.gtk_mgr.ui.add_view.cone_button);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.cone_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	g_global.r.gtk_mgr.ui.add_view.vector_img = gtk_image_new_from_file(
	"uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_img, 0, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.x, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_x, 1, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.y, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_y, 2, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.z, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_z, 3, 4, 1, 1);
	g_global.r.gtk_mgr.ui.add_view.inf_img = gtk_image_new_from_file(
	"uiconfig/infinite.png");
	end_cone_view(c);
}

void				handle_switch(t_cylinder *c, GtkAdjustment *adj)
{
	g_global.r.gtk_mgr.ui.add_view.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_y, 2, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.z, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_z, 3, 4, 1, 1);
	g_global.r.gtk_mgr.ui.add_view.inf_img = gtk_image_new_from_file(
	"uiconfig/infinite.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.inf_img, 0, 5, 1, 1);
	g_global.r.gtk_mgr.ui.add_view.infinite = gtk_switch_new();
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.infinite, 1, 5, 1, 1);
	gtk_switch_set_state(GTK_SWITCH(
	g_global.r.gtk_mgr.ui.add_view.infinite), c->infinite);
}

void				edit_cylinder_view(t_cylinder *c)
{
	GtkAdjustment	*adj_scale;
	GtkAdjustment	*adj;

	deactivate_buttons(g_global.r.gtk_mgr.ui.add_view.cylinder_button);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.cylinder_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	g_global.r.gtk_mgr.ui.add_view.scale_img = gtk_image_new_from_file(
	"uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(c->radius, 0, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.scale_spin = gtk_spin_button_new(
	adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.scale_spin, 1, 1, 3, 1);
	g_global.r.gtk_mgr.ui.add_view.vector_img = gtk_image_new_from_file(
	"uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_img, 0, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.x, -1000, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.vector_x, 1, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.y, -1000, 1000, .5, 1, 10);
	handle_switch(c, adj);
}
