/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2019/01/17 02:13:28 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				add_addendum(t_obj *o)
{
	gtk_window_set_title(GTK_WINDOW(ADD_VIEW.win), "Add Object");
	o->type = 1;
	o->next = g_global.r->objects;
	g_global.r->objects = o;
	if (!(o->obj = (t_sphere*)malloc(sizeof(t_sphere))))
		exit_properly(1);
	set_default_values(o);
}

void				actual_edit_view(t_obj *o)
{
	if (!(ADD_VIEW.translate_x_spin) && !(ADD_VIEW.translate_y_spin)
	&& !(ADD_VIEW.translate_z_spin))
	{
		gtk_window_set_title(GTK_WINDOW(ADD_VIEW.win), "Edit Object");
		handle_base_elems_edit(o);
	}
	if (o->type == -5) // Use of uninitialised value of size 8
		add_addendum(o);
	if (o->type == 1)
		edit_sphere_view((t_sphere*)o->obj);
	else if (o->type == 2)
		edit_plane_view((t_plane*)o->obj);
	else if (o->type == 3)
		edit_cone_view((t_cone*)o->obj);
	else if (o->type == 4)
		edit_cylinder_view((t_cylinder*)o->obj);
	else if (o->type / 10 == 6 || o->type == 6)
	{
		edit_poly_view();
		if (o->type == 68)
			add_height_spin();
	}
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
	ADD_VIEW.saved_type = o->type;
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
