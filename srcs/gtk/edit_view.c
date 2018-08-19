/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 15:22:20 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.gtk_mgr.pixmap
#define GTKMGR g_global.gtk_mgr

extern t_global		g_global;

static void			edit_sphere_view(t_sphere *s)
{
	(void)s;
}

static void			edit_plane_view(t_plane *p)
{
	(void)p;
}

static void			edit_cone_view(t_cone *c)
{
	(void)c;
}

static void			edit_cylinder_view(t_cylinder *c)
{
	(void)c;
}

static void			edit_poly_view(t_poly_obj *p)
{
	(void)p;
}

void				edit_win(t_obj *o)
{
	GTKMGR.ui.add_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.add_view.win), GTK_WIN_POS_MOUSE);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.add_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.add_view.win), "raytracer");
	GTKMGR.ui.add_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.add_view.win), GTKMGR.ui.add_view.grid);
	GTKMGR.ui.add_view.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
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
