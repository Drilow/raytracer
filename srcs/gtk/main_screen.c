/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:18:24 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 18:19:43 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global g_global;

void				add_view(void)
{
	t_obj			*o;

	if (!(o = (t_obj*)malloc(sizeof(t_obj))))
		exit_properly(1);
	o->type = -5;
	o->position.x = 0;
	o->position.y = 0;
	o->position.z = 0;
	o->enabled = true;
	o->obj = NULL;
	o->color.r = 0;
	o->color.g = 0;
	o->color.b = 0;
	o->color.trans = 0;
	o->reflex = 0;
	o->size = 0;
	edit_win(o, g_global.r.gtk_mgr.ui.main_view.win);
}

static void			handle_main_view_img(void)
{
	g_global.r.gtk_mgr.ui.main_view.add_img = gtk_image_new_from_file(
	"uiconfig/plus-sign-in-a-black-circle.png");
	g_global.r.gtk_mgr.ui.main_view.filters_img = gtk_image_new_from_file(
	"uiconfig/filter.png");
	g_global.r.gtk_mgr.ui.main_view.select_img = gtk_image_new_from_file(
	"uiconfig/new-file.png");
	g_global.r.gtk_mgr.ui.main_view.export_img = gtk_image_new_from_file(
	"uiconfig/scale-symbol.png");
}

void				handle_main_view(void)
{
	handle_main_view_img();
	g_global.r.gtk_mgr.ui.main_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.main_view.win), FALSE);
	gtk_window_set_position(GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win),
	GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win),
	"raytracer");
	g_global.r.gtk_mgr.ui.main_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.main_view.win),
	g_global.r.gtk_mgr.ui.main_view.grid);
	g_global.r.gtk_mgr.ui.main_view.buttonbox = gtk_button_box_new(
	GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.main_view.grid),
	g_global.r.gtk_mgr.ui.main_view.buttonbox);
	g_global.r.gtk_mgr.ui.main_view.list_button = gtk_button_new();
	g_global.r.gtk_mgr.ui.main_view.add_button = gtk_button_new();
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.main_view.add_button,
	"add object");
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.main_view.add_button),
	"clicked", G_CALLBACK(add_view), NULL);
	handle_main_view_2();
}
