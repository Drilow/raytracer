/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2018/09/02 19:53:41 by adleau           ###   ########.fr       */
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
}

void				validate_plane(t_plane *p)
{
	p->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	p->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	p->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
	printf("TA MERE\n");
}

void				validate_cone(t_cone *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
	c->angle = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin));
	c->infinite = gtk_switch_get_active(GTK_SWITCH(ADD_VIEW.infinite));
}

void				validate_cylinder(t_cylinder *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
	c->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin));
	c->infinite = gtk_switch_get_active(GTK_SWITCH(ADD_VIEW.infinite));
}

void				validate_edit(t_obj *o)
{
	o->position.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_x_spin));
	o->position.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_y_spin));
	o->position.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_z_spin));
	if (o->type == 1)
		validate_sphere((t_sphere*)o->obj);
	else if (o->type == 2)
		validate_plane((t_plane*)o->obj);
	else if (o->type == 3)
		validate_cone((t_cone*)o->obj);
	else if (o->type == 4)
		validate_cylinder((t_cylinder*)o->obj);
//	else if (o->type == 6 || o->type / 10 == 6)
//		validate_poly_obj((t_poly_obj*)o->obj);
	draw_image();
	if (PIXMAP)
		cairo_surface_destroy(PIXMAP);
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit(1);
	cairo_surface_mark_dirty(PIXMAP);
	gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area), PIXMAP);
}

static void			edit_sphere_view(t_sphere *s)
{
	GtkAdjustment	*adj_scale;

	deactivate_buttons(ADD_VIEW.sphere_button);
	if (ADD_VIEW.vector_x != NULL && ADD_VIEW.vector_y != NULL && ADD_VIEW.vector_z != NULL)
	{
		gtk_widget_destroy(ADD_VIEW.vector_x);
		gtk_widget_destroy(ADD_VIEW.vector_y);
		gtk_widget_destroy(ADD_VIEW.vector_z);
		ADD_VIEW.vector_x = NULL;
		ADD_VIEW.vector_y = NULL;
		ADD_VIEW.vector_z = NULL;
	}
	gtk_widget_set_state_flags(ADD_VIEW.sphere_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	adj_scale = gtk_adjustment_new(s->radius, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.scale_spin, 1, 1, 3, 1);
	printf("WTFBBQ\n");
}

static void			edit_plane_view(t_plane *p)
{
	GtkAdjustment	*adj;

	deactivate_buttons(ADD_VIEW.plane_button);
	if (ADD_VIEW.scale_spin != NULL)
		gtk_widget_destroy(ADD_VIEW.scale_spin);
	gtk_widget_set_state_flags(ADD_VIEW.plane_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE ,true);
	adj = gtk_adjustment_new(p->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.vector_x, 1, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.vector_y, 2, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.vector_z, 3, 1, 1, 1);
	printf("MY 2ND DICK\n");
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
	GtkAdjustment	*adj_mv;

	if (!(ADD_VIEW.translate_x_spin) && !(ADD_VIEW.translate_y_spin) && !(ADD_VIEW.translate_z_spin))
	{
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.add_view.win), "Edit Object");
	ADD_VIEW.translate_img = gtk_image_new_from_file("uiconfig/move.png");
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_img, 0, 3, 1, 1);
	adj_mv = gtk_adjustment_new(o->position.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_x_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_x_spin, 1, 3, 1, 1);
	adj_mv = gtk_adjustment_new(o->position.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_y_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_y_spin, 2, 3, 1, 1);
	adj_mv = gtk_adjustment_new(o->position.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.translate_z_spin = gtk_spin_button_new(adj_mv, 1, 4);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.translate_z_spin, 3, 3, 1, 1);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.scale_img, 0, 1, 1, 1);
	}
	if (o->type == 1)
		edit_sphere_view((t_sphere*)o->obj);
	else if (o->type == 2)
		edit_plane_view((t_plane*)o->obj);
	else if (o->type == 3)
		edit_cone_view((t_cone*)o->obj);
	else if (o->type == 4)
		edit_cylinder_view((t_cylinder*)o->obj);
	else if (o->type / 10 == 6 || o->type == 6)
		edit_poly_view((t_poly_obj*)o->obj);
}

void				set_default_values(t_obj *o)
{
	if (o->type == 1)
		((t_sphere*)o->obj)->radius = 2;
	else if (o->type == 2)
	{
		((t_plane*)o->obj)->vector.x = 1;
		((t_plane*)o->obj)->vector.y = 1;
		((t_plane*)o->obj)->vector.z = 1;
	}
	else if (o->type == 3)
	{
		((t_cone*)o->obj)->vector.x = 1;
		((t_cone*)o->obj)->vector.y = 1;
		((t_cone*)o->obj)->vector.z = 1;
		((t_cone*)o->obj)->angle = 60;
		((t_cone*)o->obj)->infinite = true;
	}
	else if (o->type == 4)
	{
		((t_cylinder*)o->obj)->vector.x = 1;
		((t_cylinder*)o->obj)->vector.y = 1;
		((t_cylinder*)o->obj)->vector.z = 1;
		((t_cylinder*)o->obj)->radius = 2;
		((t_cylinder*)o->obj)->infinite = true;
	}
}

void				create_object(t_obj *o, int type)
{
	t_obj			*tmp;

	if (!(tmp = (t_obj*)malloc(sizeof(t_obj))))
		exit(1);
	if (type == 1)
	{
		tmp->obj = (t_sphere*)malloc(sizeof(t_sphere));
		tmp->type = 1;
	}
	else if (type == 2)
	{
		tmp->obj = (t_plane*)malloc(sizeof(t_plane));
		tmp->type = 2;
	}
	else if (type == 3)
	{
		tmp->obj = (t_cone*)malloc(sizeof(t_cone));
		tmp->type = 3;
	}
	else if (type == 4)
	{
		tmp->obj = (t_cylinder*)malloc(sizeof(t_cylinder));
		tmp->type = 4;
	}
	set_default_values(tmp);
	free(o->obj);
	o->type = tmp->type;
	o->obj = tmp->obj;
}

void				switch_type(GtkButton *button)
{
	t_obj			*o;
	int				type;

	type = ADD_VIEW.sw.o->type;
	o = ADD_VIEW.sw.o;
//	destroy_interface_for_type(o);
	if (button == GTK_BUTTON(ADD_VIEW.sphere_button))
	{
		ADD_VIEW.sw.type = 1;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.plane_button))
	{
		ADD_VIEW.sw.type = 2;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.cone_button))
	{
		ADD_VIEW.sw.type = 3;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.cylinder_button))
	{
		ADD_VIEW.sw.type = 4;
	}
	create_object(o, ADD_VIEW.sw.type);
	if (o)
		actual_edit_view(o);
	gtk_widget_show_all(ADD_VIEW.win);
	return ;
}

void			init_add_view(void);

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
	gint wx, wy;

	ADD_VIEW.sw.o = o;
	gtk_widget_translate_coordinates(GTKMGR.ui.main_view.select_button, gtk_widget_get_toplevel(GTKMGR.ui.main_view.select_button), 0, 0, &wx, &wy);
	gtk_window_move(GTK_WINDOW(ADD_VIEW.win), wx, wy);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(ADD_VIEW.win));
	GTKMGR.ui.add_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), GTKMGR.ui.add_view.grid);
	GTKMGR.ui.add_view.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.add_view.grid), GTKMGR.ui.add_view.buttonbox, 0, 0, 4, 1);
	ADD_VIEW.sphere_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.sphere_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.sphere_button, "Sphere");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.sphere_button), ADD_VIEW.sphere_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.sphere_button);
	ADD_VIEW.plane_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.plane_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.plane_button, "Plane");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.plane_button), ADD_VIEW.plane_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.plane_button);
	ADD_VIEW.cone_button = gtk_button_new();
g_signal_connect(G_OBJECT(ADD_VIEW.cone_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.cone_button, "Cone");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cone_button), ADD_VIEW.cone_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.cone_button);
	ADD_VIEW.cylinder_button = gtk_button_new();
g_signal_connect(G_OBJECT(ADD_VIEW.cylinder_button), "clicked", G_CALLBACK(switch_type), NULL);
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
	printf("MYDICKISHUGE\n");
	gtk_widget_show_all(ADD_VIEW.win);
	int r;
	if ((r = gtk_dialog_run(GTK_DIALOG(ADD_VIEW.win))) == GTK_RESPONSE_ACCEPT)
	{
		printf("QUE QUOI?\n");
		validate_edit(o);
		gtk_widget_destroy(ADD_VIEW.win);
		init_add_view();
	}
	printf("RRRR %d || TYPE %d\n", r, o->type);
	if (o->type == 1)
		printf("x : %f, y : %f, z : %f, type : %d, radius : %f\n", o->position.x, o->position.y, o->position.z, o->type, ((t_sphere*)o->obj)->radius);
}
