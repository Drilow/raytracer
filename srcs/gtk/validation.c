/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 19:15:20 by adleau            #+#    #+#             */
/*   Updated: 2019/01/07 18:42:28 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view
#define SCENE_VIEW g_global.r->gtk_mgr.ui.scene_view

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
		gtk_widget_set_state_flags(ADD_VIEW.pyramid, GTK_STATE_FLAG_NORMAL, true);
}

void				validate_edit(t_obj *o)
{
	GdkRGBA			*c;

	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit(1); // to fix
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
	o->color.r = (unsigned char)(c->red * 255);
	o->color.g = (unsigned char)(c->green * 255);
	o->color.b = (unsigned char)(c->blue * 255);
	o->color.trans = ((unsigned char)255 - (c->alpha * 255));
	printf("%f\n", gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.reflex_spin)));
	o->reflex = (unsigned char)((gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.reflex_spin))));// * 255);
	printf("%u\n", o->reflex);
	o->position.x =
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_x_spin));
	o->position.y =
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_y_spin));
	o->position.z =
	gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_z_spin));
	validate_objects(o);
	redraw(true);
	gtk_widget_destroy(GTK_WIDGET(SCENE_VIEW.win));
	scene_win();
}








