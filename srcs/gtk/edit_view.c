/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2019/01/07 17:46:17 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global		g_global;

void				handle_reflex_edit(t_obj *o)
{
	GtkAdjustment	*adj;

	ADD_VIEW.reflex_img = gtk_image_new_from_file("uiconfig/reflex.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.reflex_img,
	0, 8, 1, 1);
	printf("%u, %f\n", o->reflex, (gdouble)o->reflex / 255);
	adj = gtk_adjustment_new((gdouble)(o->reflex) / 255, 0, 1, .01, .01, 10);
	ADD_VIEW.reflex_spin = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.reflex_spin,
	1, 8, 3, 1);
}

void				handle_base_elems_edit(t_obj *o)
{
	GtkAdjustment	*adj_mv;
	GdkRGBA			*c;

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
	handle_reflex_edit(o);
	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit(1); // to fix
	get_color_values(o->color, c);
	ADD_VIEW.color = gtk_color_chooser_widget_new();
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.color, 0, 9, 4, 1);
	free(c);
}

void				actual_edit_view(t_obj *o)
{
	if (!(ADD_VIEW.translate_x_spin) && !(ADD_VIEW.translate_y_spin)
	&& !(ADD_VIEW.translate_z_spin))
	{
		gtk_window_set_title(GTK_WINDOW(ADD_VIEW.win), "Edit Object");
		handle_base_elems_edit(o);
	}
	if (o->type == -5)
	{
		gtk_window_set_title(GTK_WINDOW(ADD_VIEW.win), "Add Object");
		o->type = 1;
		o->next = g_global.r->objects;
		g_global.r->objects = o;
		if (!(o->obj = (t_sphere*)malloc(sizeof(t_sphere))))
			exit(1); // to fix
		set_default_values(o);
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
		edit_poly_view();
}

void				edit_win_3(t_obj *o)
{
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cylinder_button),
	ADD_VIEW.cylinder_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox),
	ADD_VIEW.cylinder_button);
	ADD_VIEW.obj_file_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.obj_file_button), "clicked",
	G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.obj_file_button, "Obj File");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.obj_file_button),
	ADD_VIEW.obj_file_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox),
	ADD_VIEW.obj_file_button);
	actual_edit_view(o);
	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(
	GTK_DIALOG(ADD_VIEW.win), GTK_RESPONSE_ACCEPT));
	gtk_widget_show_all(ADD_VIEW.win);
	g_signal_connect(G_OBJECT(ADD_VIEW.win), "delete-event",
	G_CALLBACK(handle_x_button), NULL);
	handle_edit_validation(o);
}

void				edit_win_2(t_obj *o)
{
	g_signal_connect(G_OBJECT(ADD_VIEW.sphere_button), "clicked",
	G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.sphere_button, "Sphere");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.sphere_button),
	ADD_VIEW.sphere_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox),
	ADD_VIEW.sphere_button);
	ADD_VIEW.plane_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.plane_button), "clicked",
	G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.plane_button, "Plane");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.plane_button), ADD_VIEW.plane_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.plane_button);
	ADD_VIEW.cone_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.cone_button),
	"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.cone_button, "Cone");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cone_button), ADD_VIEW.cone_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.cone_button);
	ADD_VIEW.cylinder_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.cylinder_button),
	"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.cylinder_button, "Cylinder");
	edit_win_3(o);
}

void				edit_win(t_obj *o, GtkWidget *parent)
{
	GtkWidget		*content_area;

	init_add_view();
	ADD_VIEW.sphere_img = gtk_image_new_from_file("uiconfig/sphere.png");
	ADD_VIEW.plane_img = gtk_image_new_from_file("uiconfig/plane.png");
	ADD_VIEW.cone_img = gtk_image_new_from_file("uiconfig/cone.png");
	ADD_VIEW.cylinder_img = gtk_image_new_from_file("uiconfig/cylinder.png");
	ADD_VIEW.obj_file_img = gtk_image_new_from_file("uiconfig/poly_obj.png");
	ADD_VIEW.win = gtk_dialog_new_with_buttons("Edit Object",
	GTK_WINDOW(parent),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
	"_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(ADD_VIEW.win),
	GTK_WINDOW(parent));
	gtk_window_set_position(GTK_WINDOW(ADD_VIEW.win), GTK_WIN_POS_MOUSE);
	ADD_VIEW.sw.o = o;
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(ADD_VIEW.win));
	ADD_VIEW.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), ADD_VIEW.grid);
	ADD_VIEW.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.buttonbox, 0, 0, 4, 1);
	ADD_VIEW.sphere_button = gtk_button_new();
	edit_win_2(o);
}
