/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_view2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:36:43 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:57:46 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				init_filter_img(void)
{
	g_global.r.gtk_mgr.ui.
	filter_view.bw_img = gtk_image_new_from_file("uiconfig/bw.png");
	g_global.r.gtk_mgr.ui.
	filter_view.sepia_img = gtk_image_new_from_file("uiconfig/sepia.png");
	g_global.r.gtk_mgr.ui.
	filter_view.reversed_img = gtk_image_new_from_file("uiconfig/reversed.png");
	g_global.r.gtk_mgr.ui.filter_view.win = gtk_dialog_new_with_buttons(
	"Filters", GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "_OK",
	GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.filter_view.win),
	GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win));
}

void				end_filters2(void)
{
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.sepia_button),
	g_global.r.gtk_mgr.ui.filter_view.sepia_img);
	gtk_container_add(GTK_CONTAINER(
	g_global.r.gtk_mgr.ui.filter_view.buttonbox),
	g_global.r.gtk_mgr.ui.filter_view.sepia_button);
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.reversed_button),
	g_global.r.gtk_mgr.ui.filter_view.reversed_img);
}
