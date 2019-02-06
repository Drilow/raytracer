/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_base_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:04:16 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 16:52:40 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				validate_sphere(t_sphere *s)
{
	s->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.scale_spin));
}

void				validate_plane(t_plane *p)
{
	p->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_x));
	p->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_y));
	p->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_z));
}

void				validate_cone(t_cone *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_z));
	c->angle = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.angle_spin)) / 360 * (PI * 2);
	c->infinite = gtk_switch_get_active(GTK_SWITCH(
	g_global.r.gtk_mgr.ui.add_view.infinite));
}

void				validate_cylinder(t_cylinder *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.vector_z));
	c->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.scale_spin));
	c->infinite = gtk_switch_get_active(GTK_SWITCH(
	g_global.r.gtk_mgr.ui.add_view.infinite));
}

bool				go_throu_lights(t_light *curr)
{
	t_light				*tmp;

	tmp = g_global.r.lights;
	while (tmp)
	{
		if (curr == tmp)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
