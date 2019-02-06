/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:50:05 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:14:58 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				switch_type(GtkButton *button)
{
	t_obj			*o;
	int				type;

	type = g_global.r.gtk_mgr.ui.add_view.sw.o->type;
	o = g_global.r.gtk_mgr.ui.add_view.sw.o;
	destroy_interface_for_type(o->type);
	if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.sphere_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 1;
	else if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.plane_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 2;
	else if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.cone_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 3;
	else if (button == GTK_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.cylinder_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 4;
	else if (button == GTK_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.obj_file_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 6;
	create_object(o, g_global.r.gtk_mgr.ui.add_view.sw.type);
	if (o)
		actual_edit_view(o);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.add_view.win);
}
