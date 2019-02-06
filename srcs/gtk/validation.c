/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 19:15:20 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:36:04 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

extern t_global		g_global;

void				deactivate_buttons_from_tp(GtkWidget *except)
{
	if (&(g_global.r.gtk_mgr.ui.add_view.cube) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.cube,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.tetra) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.tetra,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.dode) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.dode,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.add_view.pyramid) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.pyramid,
		GTK_STATE_FLAG_NORMAL, true);
}

void				validate_rotate(t_obj *o)
{
	t_rpoint		r;

	r.x = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.rotate_x_spin))
	/ 360 * (2 * PI);
	r.y = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.rotate_y_spin))
	/ 360 * (2 * PI);
	r.z = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.rotate_z_spin))
	/ 360 * (2 * PI);
	if (r.x != 0 || r.y != 0 || r.z != 0)
		rotate_obj(o, o->type, r);
}

t_rgb				get_color_from_chooser(GdkRGBA *c)
{
	t_rgb			color;

	color.r = (unsigned char)(c->red * 255);
	color.g = (unsigned char)(c->green * 255);
	color.b = (unsigned char)(c->blue * 255);
	color.trans = ((unsigned char)255 - (c->alpha * 255));
	return (color);
}

void				validate_edit(t_obj *o)
{
	GdkRGBA			*c;

	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit_properly(1);
	gtk_color_chooser_get_rgba(
	GTK_COLOR_CHOOSER(g_global.r.gtk_mgr.ui.add_view.color), c);
	o->color = get_color_from_chooser(c);
	o->reflex = (unsigned char)
	((gtk_spin_button_get_value(GTK_SPIN_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.reflex_spin))));
	o->position.x = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.translate_x_spin));
	o->position.y = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.translate_y_spin));
	o->position.z = gtk_spin_button_get_value(
	GTK_SPIN_BUTTON(g_global.r.gtk_mgr.ui.add_view.translate_z_spin));
	validate_objects(o);
	validate_rotate(o);
	redraw(true);
	free(c);
	c = NULL;
	gtk_tree_store_clear(g_global.r.gtk_mgr.ui.scene_view.store);
	gtk_widget_destroy(GTK_WIDGET(g_global.r.gtk_mgr.ui.scene_view.win));
	scene_win();
}
