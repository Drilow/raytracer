/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:50:05 by adleau            #+#    #+#             */
/*   Updated: 2019/01/15 04:51:45 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#include <display/display.h>

extern t_global		g_global;

void				switch_type(GtkButton *button)
{
	t_obj			*o;
	int				type;

	type = ADD_VIEW.sw.o->type;
	o = ADD_VIEW.sw.o;
	destroy_interface_for_type(o->type);
	if (button == GTK_BUTTON(ADD_VIEW.sphere_button))
		ADD_VIEW.sw.type = 1;
	else if (button == GTK_BUTTON(ADD_VIEW.plane_button))
		ADD_VIEW.sw.type = 2;
	else if (button == GTK_BUTTON(ADD_VIEW.cone_button))
		ADD_VIEW.sw.type = 3;
	else if (button == GTK_BUTTON(ADD_VIEW.cylinder_button))
		ADD_VIEW.sw.type = 4;
	else if (button == GTK_BUTTON(ADD_VIEW.obj_file_button))
		ADD_VIEW.sw.type = 6;
	create_object(o, ADD_VIEW.sw.type);
	if (o)
		actual_edit_view(o);
	gtk_widget_show_all(ADD_VIEW.win);
}
