/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:18:32 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:32:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

extern t_global		g_global;

void				validate_same_obj(t_obj *o)
{
	if (o->type > 60)
		free_poly((t_poly_obj*)g_global.r.gtk_mgr.ui.add_view.sw.o->obj);
	if (o->type == 66)
		set_cube(g_global.r.gtk_mgr.ui.add_view.sw.o->position,
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.scale_spin))
	* 2, g_global.r.gtk_mgr.ui.add_view.sw.o);
	else if (o->type == 67)
		set_tetrahedron(g_global.r.gtk_mgr.ui.add_view.sw.o->position,
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.scale_spin)),
	g_global.r.gtk_mgr.ui.add_view.sw.o);
	else if (o->type == 68)
		get_pyramid(g_global.r.gtk_mgr.ui.add_view.sw.o,
		gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.scale_spin)),
		gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.height_spin)));
	else if (o->type == 69)
		get_dodecahedron(g_global.r.gtk_mgr.ui.add_view.sw.o,
		gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.scale_spin)));
}

void				validate_from_file(char *path)
{
	validate_obj(g_global.r.gtk_mgr.ui.add_view.sw.o->position,
	gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.scale_spin)),
	path, g_global.r.gtk_mgr.ui.add_view.sw.o);
	set_obj(g_global.r.gtk_mgr.ui.add_view.sw.o);
}

void				from_tp_add(t_obj *o)
{
	if (o->type == 6)
		validate_from_file(
		g_global.r.gtk_mgr.ui.add_view.obj_file_path);
	else if (o->type == 66)
		set_cube(o->position,
		gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.scale_spin)) * 2, o);
	else if (o->type == 67)
		set_tetrahedron(o->position,
		gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.scale_spin)), o);
	else if (o->type == 68)
		get_pyramid(g_global.r.gtk_mgr.ui.add_view.sw.o,
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.scale_spin)),
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.height_spin)));
	else if (o->type == 69)
		get_dodecahedron(g_global.r.gtk_mgr.ui.add_view.sw.o,
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(
		g_global.r.gtk_mgr.ui.add_view.scale_spin)));
}

void				validate_poly_obj(t_obj *o)
{
	if (gtk_toggle_button_get_active(
	GTK_TOGGLE_BUTTON(g_global.r.gtk_mgr.ui.add_view.same)))
		validate_same_obj(o);
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.from_template)))
	{
		from_tp_add(o);
	}
	else
		validate_from_file(g_global.r.gtk_mgr.ui.add_view.obj_file_path);
}

void				validate_objects(t_obj *o)
{
	if (o->type == 1)
		validate_sphere((t_sphere*)o->obj);
	else if (o->type == 2)
		validate_plane((t_plane*)o->obj);
	else if (o->type == 3)
		validate_cone((t_cone*)o->obj);
	else if (o->type == 4)
		validate_cylinder((t_cylinder*)o->obj);
	else if (o->type == 6 || o->type / 10 == 6)
		validate_poly_obj(o);
}
