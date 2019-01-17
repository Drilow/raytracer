/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_handlers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:52:28 by adleau            #+#    #+#             */
/*   Updated: 2019/01/16 22:58:12 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#include <display/display.h>

extern t_global		g_global;

void				set_for_cone(t_obj *o)
{
	((t_cone*)o->obj)->vector.x = 1;
	((t_cone*)o->obj)->vector.y = 1;
	((t_cone*)o->obj)->vector.z = 1;
	((t_cone*)o->obj)->angle = (double)60 / 360;
	((t_cone*)o->obj)->infinite = true;
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
		set_for_cone(o);
	else if (o->type == 4)
	{
		((t_cylinder*)o->obj)->vector.x = 1;
		((t_cylinder*)o->obj)->vector.y = 1;
		((t_cylinder*)o->obj)->vector.z = 1;
		((t_cylinder*)o->obj)->radius = 2;
		((t_cylinder*)o->obj)->infinite = true;
	}
	else if (o->type == 6 || o->type / 10 == 6)
	{
		ADD_VIEW.sw.o->size = 2;
		((t_poly_obj*)(o->obj))->vertices = NULL;
		((t_poly_obj*)(o->obj))->next = NULL;
	}
}

void				deactivate_buttons(GtkWidget *except)
{
	if (&(ADD_VIEW.sphere_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.sphere_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.plane_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.plane_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.cone_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cone_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.cylinder_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cylinder_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.obj_file_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.obj_file_button,
		GTK_STATE_FLAG_NORMAL, true);
}

void				redraw_if_false(void)
{
	free(GTKMGR.buf);
	GTKMGR.buf = NULL;
	if (!(GTKMGR.buf = ft_ustrdup(GTKMGR.saved,
	WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
		exit(1); //to fix
	if (PIXMAP)
	{
		cairo_surface_destroy(PIXMAP);
		PIXMAP = NULL;
	}
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.saved,
	CAIRO_FORMAT_RGB24,
	WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
//	free(GTKMGR.buf);
//	GTKMGR.buf = NULL;
}

void				redraw(bool display)
{
	if (display == true)
	{
		if (!GTKMGR.buf)
			if (!(GTKMGR.buf
= (unsigned char*)malloc(sizeof(unsigned char) * WIN_H
* cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
				exit_properly(1);
		draw_image();
		if (PIXMAP)
			cairo_surface_destroy(PIXMAP);
		PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf,
		CAIRO_FORMAT_RGB24,
		WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	}
	else
		redraw_if_false();
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit_properly(1);
	cairo_surface_mark_dirty(PIXMAP);
	gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area),
	PIXMAP);
}
