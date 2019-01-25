/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 19:15:20 by adleau            #+#    #+#             */
/*   Updated: 2019/01/25 14:17:52 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				deactivate_buttons_from_tp(GtkWidget *except)
{
	if (&(ADD_VIEW.cube) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cube, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.tetra) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.tetra, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.dode) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.dode, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.pyramid) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.pyramid, GTK_STATE_FLAG_NORMAL,
		true);
}

void				validate_rotate(t_obj *o)
{
	t_rpoint		r;

	r.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.rotate_x_spin));
	r.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.rotate_y_spin));
	r.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.rotate_z_spin));
	rotate_obj(o, o->type, r);
}

void				validate_edit(t_obj *o)
{
	GdkRGBA			*c;

	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit_properly(1);
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
	o->color.r = (unsigned char)(c->red * 255);
	o->color.g = (unsigned char)(c->green * 255);
	o->color.b = (unsigned char)(c->blue * 255);
	o->color.trans = ((unsigned char)255 - (c->alpha * 255));
	o->reflex = (unsigned char)
	((gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.reflex_spin))));
	o->position.x = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(ADD_VIEW.translate_x_spin));
	o->position.y = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(ADD_VIEW.translate_y_spin));
	o->position.z = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(ADD_VIEW.translate_z_spin));
	validate_objects(o);
	validate_rotate(o);
	redraw(true);
	free(c);
	c = NULL;
	gtk_tree_store_clear(SCENE_VIEW.store);
	gtk_widget_destroy(GTK_WIDGET(SCENE_VIEW.win));
	scene_win();
}
