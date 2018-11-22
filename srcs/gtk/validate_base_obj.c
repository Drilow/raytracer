/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_base_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:04:16 by adleau            #+#    #+#             */
/*   Updated: 2018/11/22 20:20:59 by adleau           ###   ########.fr       */
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

void				validate_sphere(t_sphere *s)
{
	s->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin));
}

void				validate_plane(t_plane *p)
{
	p->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	p->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	p->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
}

void				validate_cone(t_cone *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
	c->angle = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.angle_spin))
	/ 360;
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
