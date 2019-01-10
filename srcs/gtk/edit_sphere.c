/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:22:54 by adleau            #+#    #+#             */
/*   Updated: 2018/12/19 13:02:09 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				edit_sphere_view(t_sphere *s)
{
	GtkAdjustment	*adj_scale;

	deactivate_buttons(ADD_VIEW.sphere_button);
	gtk_widget_set_state_flags(ADD_VIEW.sphere_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(s->radius, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_spin, 1, 1, 3, 1);
}
