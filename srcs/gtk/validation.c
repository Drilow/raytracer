/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 19:15:20 by adleau            #+#    #+#             */
/*   Updated: 2018/10/04 15:05:41 by adleau           ###   ########.fr       */
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

void				deactivate_buttons_from_tp(GtkWidget *except)
{
	if (&(ADD_VIEW.cube) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cube, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.tetra) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.tetra, GTK_STATE_FLAG_NORMAL, true);
}

void				validate_same_obj(t_obj *o)
{
	if (o->type == 66)
		set_cube(ADD_VIEW.sw.o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)) * 2, ADD_VIEW.sw.o);
	else if (o->type == 67)
		set_tetrahedron(ADD_VIEW.sw.o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), ADD_VIEW.sw.o);
}

void				validate_from_file(char *path)
{
	validate_obj(ADD_VIEW.sw.o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), path, ADD_VIEW.sw.o);
	set_obj(ADD_VIEW.sw.o);
}

void				validate_poly_obj(t_obj *o)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ADD_VIEW.same)))
		validate_same_obj(o);
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ADD_VIEW.from_template)))
	{
		if (o->type == 6)
			validate_from_file(ADD_VIEW.obj_file_path);
		else if (o->type == 66)
			set_cube(o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)) * 2, o);
		else if (o->type == 67)
			set_tetrahedron(o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), o);
	}
	else
		validate_from_file(ADD_VIEW.obj_file_path);
}

void				validate_edit(t_obj *o)
{
	GdkRGBA			*c;

	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit(1);
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
	o->color.r = (unsigned char)(c->red * 255);
	o->color.g = (unsigned char)(c->green * 255);
	o->color.b = (unsigned char)(c->blue * 255);
	o->color.trans = (unsigned char)(c->alpha);
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
	else if (o->type == 6 || o->type / 10 == 6)
		validate_poly_obj(o);
	redraw(true);
}

