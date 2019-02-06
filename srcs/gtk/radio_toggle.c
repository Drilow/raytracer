/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio_toggle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:12:58 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:17:23 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				radio_toggle_2(void)
{
	if (g_global.r.gtk_mgr.ui.add_view.cube)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.cube);
		g_global.r.gtk_mgr.ui.add_view.cube = NULL;
	}
	if (g_global.r.gtk_mgr.ui.add_view.tetra)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.tetra);
		g_global.r.gtk_mgr.ui.add_view.tetra = NULL;
	}
	if (g_global.r.gtk_mgr.ui.add_view.dode)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.dode);
		g_global.r.gtk_mgr.ui.add_view.tetra = NULL;
	}
	if (g_global.r.gtk_mgr.ui.add_view.pyramid)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.pyramid);
		g_global.r.gtk_mgr.ui.add_view.tetra = NULL;
	}
}

void				radio_toggle1_5(void)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.same), false);
	gtk_toggle_button_set_active(
	GTK_TOGGLE_BUTTON(g_global.r.gtk_mgr.ui.add_view.from_template), true);
}

void				radio_toggle(GtkWidget *button)
{
	if (g_global.r.gtk_mgr.ui.add_view.height_img)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_img);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.height_spin);
		g_global.r.gtk_mgr.ui.add_view.height_img = NULL;
	}
	if (button == g_global.r.gtk_mgr.ui.add_view.file_check)
		for_file(button);
	if (button == g_global.r.gtk_mgr.ui.add_view.from_template)
	{
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
			for_template();
		else
			radio_toggle_2();
	}
	if (g_global.r.gtk_mgr.ui.add_view.saved_type == 68
	&& (button == g_global.r.gtk_mgr.ui.add_view.same))
		add_height_spin();
	if (g_global.r.gtk_mgr.ui.add_view.saved_type / 10 != 6
	&& g_global.r.gtk_mgr.ui.add_view.saved_type != 6
	&& button == g_global.r.gtk_mgr.ui.add_view.same)
		radio_toggle1_5();
}
