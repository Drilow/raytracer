/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:40:41 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:19:34 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <display/display.h>

extern t_global				g_global;

void						handle_x_button(GtkWidget *w)
{
	if (w == g_global.r.gtk_mgr.ui.add_view.win)
	{
		if (!(g_global.r.gtk_mgr.ui.progress_data.window))
		{
			redraw(false);
			gtk_widget_destroy(GTK_WIDGET(w));
		}
		return ;
	}
	else if (w == g_global.r.gtk_mgr.ui.main_view.win)
		exit_properly(0);
	else if (w == g_global.base_view.win)
	{
		gtk_main_quit();
	}
	if (GTK_IS_WIDGET(w))
	{
		gtk_widget_destroy(GTK_WIDGET(w));
		w = NULL;
	}
}

void						on_key_press_2(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape
	&& w != NULL && w != g_global.r.gtk_mgr.ui.progress_data.window)
	{
		if (w == g_global.r.gtk_mgr.ui.main_view.win)
		{
			if (GTK_IS_WIDGET(w))
			{
				gtk_widget_destroy(GTK_WIDGET(w));
				w = NULL;
			}
			exit_properly(0);
		}
	}
}

void						on_key_press(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval != GDK_KEY_Escape)
		return ;
	if (w == g_global.base_view.win && event->keyval == GDK_KEY_Escape)
	{
		if (g_global.r.objects)
			free_objects(g_global.r.objects);
		gtk_main_quit();
		return ;
	}
	if (event->keyval == GDK_KEY_Escape
	&& w == g_global.r.gtk_mgr.ui.filter_view.win)
	{
		redraw(true);
		gtk_widget_destroy(w);
		return ;
	}
	if (w == g_global.r.gtk_mgr.ui.add_view.win
	&& event->keyval == GDK_KEY_Escape)
	{
		redraw(false);
		return ;
	}
	on_key_press_2(w, event);
}
