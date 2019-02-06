/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 18:33:05 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				add_addendum(t_obj *o)
{
	gtk_window_set_title(GTK_WINDOW(g_global.r.gtk_mgr.ui.add_view.win),
		"Add Object");
	o->type = 1;
	o->next = g_global.r.objects;
	g_global.r.objects = o;
	if (!(o->obj = (t_sphere*)malloc(sizeof(t_sphere))))
		exit_properly(1);
	set_default_values(o);
}

void				actual_edit_view(t_obj *o)
{
	if (!(g_global.r.gtk_mgr.ui.add_view.translate_x_spin)
	&& !(g_global.r.gtk_mgr.ui.add_view.translate_y_spin)
	&& !(g_global.r.gtk_mgr.ui.add_view.translate_z_spin))
	{
		gtk_window_set_title(GTK_WINDOW(g_global.r.gtk_mgr.ui.add_view.win),
			"Edit Object");
		handle_base_elems_edit(o);
	}
	if (o->type == -5)
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
	edit_win_4();
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.cylinder_button,
		"Cylinder");
	gtk_button_set_image(GTK_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.cylinder_button),
	g_global.r.gtk_mgr.ui.add_view.cylinder_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.add_view.buttonbox),
		g_global.r.gtk_mgr.ui.add_view.cylinder_button);
	g_global.r.gtk_mgr.ui.add_view.obj_file_button = gtk_button_new();
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.obj_file_button),
		"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.obj_file_button,
		"Obj File");
	gtk_button_set_image(GTK_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.obj_file_button),
		g_global.r.gtk_mgr.ui.add_view.obj_file_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.add_view.buttonbox),
		g_global.r.gtk_mgr.ui.add_view.obj_file_button);
	actual_edit_view(o);
	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(
	GTK_DIALOG(g_global.r.gtk_mgr.ui.add_view.win), GTK_RESPONSE_ACCEPT));
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.add_view.win);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.win),
		"delete-event", G_CALLBACK(handle_x_button), NULL);
	handle_edit_validation(o);
}

void				edit_win_2(t_obj *o)
{
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.sphere_button),
		"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.sphere_button,
		"Sphere");
	gtk_button_set_image(GTK_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.sphere_button),
		g_global.r.gtk_mgr.ui.add_view.sphere_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.add_view.buttonbox),
	g_global.r.gtk_mgr.ui.add_view.sphere_button);
	g_global.r.gtk_mgr.ui.add_view.plane_button = gtk_button_new();
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.plane_button),
		"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.plane_button,
		"Plane");
	gtk_button_set_image(GTK_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.plane_button),
		g_global.r.gtk_mgr.ui.add_view.plane_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.add_view.buttonbox),
		g_global.r.gtk_mgr.ui.add_view.plane_button);
	g_global.r.gtk_mgr.ui.add_view.cone_button = gtk_button_new();
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.cone_button),
	"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.cone_button,
		"Cone");
	edit_win_3(o);
}

void				edit_win(t_obj *o, GtkWidget *parent)
{
	GtkWidget		*content_area;

	if (g_global.r.gtk_mgr.ui.progress_data.window)
		return ;
	init_add_view();
	edit_win_img_init(o);
	g_global.r.gtk_mgr.ui.add_view.win = gtk_dialog_new_with_buttons(
		"Edit Object", GTK_WINDOW(parent),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
	"_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(g_global.r.gtk_mgr.ui.add_view.win),
	GTK_WINDOW(parent));
	gtk_window_set_position(GTK_WINDOW(g_global.r.gtk_mgr.ui.add_view.win),
		GTK_WIN_POS_MOUSE);
	g_global.r.gtk_mgr.ui.add_view.sw.o = o;
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(
		g_global.r.gtk_mgr.ui.add_view.win));
	g_global.r.gtk_mgr.ui.add_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area),
		g_global.r.gtk_mgr.ui.add_view.grid);
	g_global.r.gtk_mgr.ui.add_view.buttonbox = gtk_button_box_new(
		GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
		g_global.r.gtk_mgr.ui.add_view.buttonbox, 0, 0, 4, 1);
	g_global.r.gtk_mgr.ui.add_view.sphere_button = gtk_button_new();
	edit_win_2(o);
}
