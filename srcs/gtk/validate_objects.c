/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:18:32 by adleau            #+#    #+#             */
/*   Updated: 2019/01/02 21:02:27 by adleau           ###   ########.fr       */
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

void				validate_same_obj(t_obj *o)
{
	if (o->type == 66)
		set_cube(ADD_VIEW.sw.o->position,
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)) * 2,
	ADD_VIEW.sw.o);
	else if (o->type == 67)
		set_tetrahedron(ADD_VIEW.sw.o->position,
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)),
	ADD_VIEW.sw.o);
/*		else if (o->type == 68)
			set_pyramid(o->position,
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), o);
		else if (o->type == 69)
			set_dodecahedron(o->position,
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), o);*/
}

void				validate_from_file(char *path)
{
	validate_obj(ADD_VIEW.sw.o->position,
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)),
	path, ADD_VIEW.sw.o);
	set_obj(ADD_VIEW.sw.o);
}

void				validate_poly_obj(t_obj *o)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ADD_VIEW.same)))
		validate_same_obj(o);
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(
	ADD_VIEW.from_template)))
	{
		if (o->type == 6)
			validate_from_file(ADD_VIEW.obj_file_path);
		else if (o->type == 66)
			set_cube(o->position,
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)) * 2, o);
		else if (o->type == 67)
			set_tetrahedron(o->position,
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), o);
/*		else if (o->type == 68)
			set_pyramid(o->position,
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), o);
		else if (o->type == 69)
			set_dodecahedron(o->position,
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), o);*/
	}
	else
		validate_from_file(ADD_VIEW.obj_file_path);
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

gboolean			is_obj(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4 || type == 6
			|| type == 66 || type == 67 || type == 68 || type == 69)
		return (TRUE);
	return (FALSE);
}
