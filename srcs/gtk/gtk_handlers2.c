/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_handlers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:52:28 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:24:44 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
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
		g_global.r.gtk_mgr.ui.add_view.sw.o->size = 2;
		((t_poly_obj*)(o->obj))->vertices = NULL;
		((t_poly_obj*)(o->obj))->next = NULL;
	}
}

void				deactivate_buttons(GtkWidget *except)
{
	if (&(g_global.r.gtk_mgr.ui.add_view.sphere_button) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.sphere_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.plane_button) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.plane_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.cone_button) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.cone_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.cylinder_button) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.cylinder_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.obj_file_button) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.obj_file_button,
		GTK_STATE_FLAG_NORMAL, true);
}

void				redraw_if_false(void)
{
	free(g_global.r.gtk_mgr.buf);
	g_global.r.gtk_mgr.buf = NULL;
	if (!(g_global.r.gtk_mgr.buf = ft_ustrdup(g_global.r.gtk_mgr.saved,
	WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
		exit_properly(1);
	if (g_global.r.gtk_mgr.pixmap)
	{
		cairo_surface_destroy(g_global.r.gtk_mgr.pixmap);
		g_global.r.gtk_mgr.pixmap = NULL;
	}
	g_global.r.gtk_mgr.pixmap = cairo_image_surface_create_for_data(g_global.r.gtk_mgr.saved,
	CAIRO_FORMAT_RGB24,
	WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
}

void				redraw(bool display)
{
	if (display == true)
	{
		if (!g_global.r.gtk_mgr.buf)
			if (!(g_global.r.gtk_mgr.buf = (
				unsigned char*)malloc(sizeof(unsigned char
				) * WIN_H * cairo_format_stride_for_width(
					CAIRO_FORMAT_RGB24, WIN_W))))
				exit_properly(1);
		draw_image();
		if (g_global.r.gtk_mgr.pixmap)
			cairo_surface_destroy(g_global.r.gtk_mgr.pixmap);
		g_global.r.gtk_mgr.pixmap = cairo_image_surface_create_for_data(g_global.r.gtk_mgr.buf,
		CAIRO_FORMAT_RGB24,
		WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	}
	else
		redraw_if_false();
	if (cairo_surface_status(g_global.r.gtk_mgr.pixmap) != CAIRO_STATUS_SUCCESS)
		exit_properly(1);
	cairo_surface_mark_dirty(g_global.r.gtk_mgr.pixmap);
	gtk_image_set_from_surface(GTK_IMAGE(g_global.r.gtk_mgr.ui.main_view.render_area),
	g_global.r.gtk_mgr.pixmap);
}
