/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2018/08/21 16:01:45 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.gtk_mgr.pixmap
#define GTKMGR g_global.gtk_mgr
#define ADD_VIEW g_global.gtk_mgr.ui.add_view

extern t_global		g_global;

void				draw_image(void);

void				deactivate_buttons(GtkWidget *except)
{
	if (&(ADD_VIEW.sphere_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.sphere_button,GTK_STATE_FLAG_NORMAL ,true);
	if (&(ADD_VIEW.plane_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.plane_button,GTK_STATE_FLAG_NORMAL ,true);
	if (&(ADD_VIEW.cone_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cone_button,GTK_STATE_FLAG_NORMAL ,true);
	if (&(ADD_VIEW.cylinder_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cylinder_button,GTK_STATE_FLAG_NORMAL ,true);
	if (&(ADD_VIEW.obj_file_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.obj_file_button,GTK_STATE_FLAG_NORMAL ,true);
}

void				validate_sphere(t_sphere *s)
{
	s->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin));
	printf("doko %f\n", s->radius);
	s->center.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_x_spin));
	printf("doko\n");
	s->center.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_y_spin));
	printf("doko\n");
	s->center.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_z_spin));
	printf("doko\n");
	draw_image();
	if (PIXMAP)
		cairo_surface_destroy(PIXMAP);
	printf("doko1\n");
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	printf("doko\n");
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit(1);
	printf("doko\n");
	cairo_surface_mark_dirty(PIXMAP);
	printf("doko\n");
	gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area), PIXMAP);
	printf("doko3\n");
}

static void			edit_sphere_view(t_sphere *s)
{
	GtkAdjustment	*adj_scale;
	GtkAdjustment	*adj_mv_x;
	GtkAdjustment	*adj_mv_y;
	GtkAdjustment	*adj_mv_z;

	deactivate_buttons(ADD_VIEW.sphere_button);
	gtk_widget_set_state_flags(ADD_VIEW.sphere_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE ,true);
	adj_scale = gtk_adjustment_new(s->radius, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	printf("wololo %f\n", s->radius);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.scale_img, 0, 1, 1, 1);
	printf("wololo\n");
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.scale_spin, 1, 1, 3, 1);
	printf("wololo\n");
	ADD_VIEW.translate_img = gtk_image_new_from_file("uiconfig/move.png");
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_img, 0, 3, 1, 1);
	printf("wololo\n");
	adj_mv_x = gtk_adjustment_new(s->center.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_x_spin = gtk_spin_button_new(adj_mv_x, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_x_spin, 1, 3, 1, 1);
	printf("wololo\n");
	adj_mv_y = gtk_adjustment_new(s->center.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_y_spin = gtk_spin_button_new(adj_mv_y, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_y_spin, 2, 3, 1, 1);
	printf("wololo\n");
	adj_mv_z = gtk_adjustment_new(s->center.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_z_spin = gtk_spin_button_new(adj_mv_z, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_z_spin, 3, 3, 1, 1);
	printf("wololo\n");
}

static void			edit_plane_view(t_plane *p)
{
	deactivate_buttons(ADD_VIEW.plane_button);
	gtk_widget_set_state_flags(ADD_VIEW.plane_button,GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE ,true);
	(void)p;
}

static void			edit_cone_view(t_cone *c)
{
	deactivate_buttons(ADD_VIEW.cone_button);
	gtk_widget_set_state_flags(ADD_VIEW.cone_button,GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE ,true);
	(void)c;
}

static void			edit_cylinder_view(t_cylinder *c)
{
	deactivate_buttons(ADD_VIEW.cylinder_button);
	gtk_widget_set_state_flags(ADD_VIEW.cylinder_button,GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE ,true);
	(void)c;
}

static void			edit_poly_view(t_poly_obj *p)
{
	deactivate_buttons(ADD_VIEW.obj_file_button);
	gtk_widget_set_state_flags(ADD_VIEW.obj_file_button,GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE ,true);
	(void)p;
}

static void			actual_edit_view(t_obj *o)
{
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.add_view.win), "Edit Object");
	if (o->type == 1)
		edit_sphere_view((t_sphere*)o->obj);
	else if (o->type == 2)
		edit_plane_view((t_plane*)o->obj);
	else if (o->type == 3)
		edit_cone_view((t_cone*)o->obj);
	else if (o->type == 4)
		edit_cylinder_view((t_cylinder*)o->obj);
	else if (o->type == 6)
		edit_poly_view((t_poly_obj*)o->obj);
}

void				edit_win(t_obj *o)
{
	GtkWidget		*content_area;

	ADD_VIEW.sphere_img = gtk_image_new_from_file("uiconfig/sphere.png");
	ADD_VIEW.plane_img = gtk_image_new_from_file("uiconfig/plane.png");
	ADD_VIEW.cone_img = gtk_image_new_from_file("uiconfig/cone.png");
	ADD_VIEW.cylinder_img = gtk_image_new_from_file("uiconfig/cylinder.png");
	ADD_VIEW.obj_file_img = gtk_image_new_from_file("uiconfig/poly_obj.png");
	GTKMGR.ui.add_view.win = gtk_dialog_new_with_buttons ("My dialog",
														  GTK_WINDOW(GTKMGR.ui.main_view.win),
														  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
														  "_OK",
														  GTK_RESPONSE_ACCEPT,
														  "_Cancel",
														  GTK_RESPONSE_REJECT,
														  NULL);
	gtk_window_set_transient_for(GTK_WINDOW(ADD_VIEW.win), GTK_WINDOW(GTKMGR.ui.main_view.win));
	printf("WQEQWEQWEQWE\n");
	gint wx, wy;
	gtk_widget_translate_coordinates(GTKMGR.ui.main_view.select_button, gtk_widget_get_toplevel(GTKMGR.ui.main_view.select_button), 0, 0, &wx, &wy);
	printf("%D %D\n", wx, wy);
	gtk_window_move(GTK_WINDOW(ADD_VIEW.win), wx, wy);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(ADD_VIEW.win));
	GTKMGR.ui.add_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), GTKMGR.ui.add_view.grid);
	GTKMGR.ui.add_view.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.buttonbox, 0, 0, 4, 1);
	ADD_VIEW.sphere_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.sphere_button), "clicked", G_CALLBACK(edit_sphere_view), o);
	gtk_widget_set_tooltip_text(ADD_VIEW.sphere_button, "Sphere");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.sphere_button), ADD_VIEW.sphere_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.sphere_button);
	ADD_VIEW.plane_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.plane_button), "clicked", G_CALLBACK(edit_plane_view), o);
	gtk_widget_set_tooltip_text(ADD_VIEW.plane_button, "Plane");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.plane_button), ADD_VIEW.plane_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.plane_button);
	ADD_VIEW.cone_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.cone_button), "clicked", G_CALLBACK(edit_cone_view), o);
	gtk_widget_set_tooltip_text(ADD_VIEW.cone_button, "Cone");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cone_button), ADD_VIEW.cone_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.cone_button);
	ADD_VIEW.cylinder_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.cylinder_button), "clicked", G_CALLBACK(edit_cylinder_view), o);
	gtk_widget_set_tooltip_text(ADD_VIEW.cylinder_button, "Cylinder");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cylinder_button), ADD_VIEW.cylinder_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.cylinder_button);
	ADD_VIEW.obj_file_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.obj_file_button), "clicked", G_CALLBACK(edit_poly_view), o);
	gtk_widget_set_tooltip_text(ADD_VIEW.obj_file_button, "Obj File");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.obj_file_button), ADD_VIEW.obj_file_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.obj_file_button);
	if (o)
		actual_edit_view(o);
	gtk_widget_show_all(ADD_VIEW.win);
	if (gtk_dialog_run(GTK_DIALOG(ADD_VIEW.win)) == GTK_RESPONSE_ACCEPT)
	{
		if (o->type == 1)
			validate_sphere((t_sphere*)o->obj);
		gtk_widget_destroy(ADD_VIEW.win);
	}
}
