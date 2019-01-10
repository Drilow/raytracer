/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:40:41 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 16:41:59 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view
#define PROGRESS_DATA g_global.r->gtk_mgr.ui.progress_data
#define FILTER_VIEW GTKMGR.ui.filter_view

extern t_global				g_global;

void						on_key_press_2(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape &&
	w != NULL && w != PROGRESS_DATA.window)
	{
		if (w == GTKMGR.ui.main_view.win)
		{
			free_objects(g_global.r->objects);
		}
		if (GTK_IS_WIDGET(w))
		{
			gtk_widget_destroy(GTK_WIDGET(w));
			w = NULL;
		}
	}
}

void						on_key_press(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval != GDK_KEY_Escape)
		return ;
	if (w == g_global.base_view.win && event->keyval == GDK_KEY_Escape)
	{
		if (g_global.r)
			free_objects(g_global.r->objects);
		gtk_main_quit();
		return ;
	}
	if (event->keyval == GDK_KEY_Escape && w == FILTER_VIEW.win)
	{
		redraw(true);
		gtk_widget_destroy(w);
		return ;
	}
	if (g_global.r && w == ADD_VIEW.win && event->keyval == GDK_KEY_Escape)
	{
		redraw(false);
		return ;
	}
	on_key_press_2(w, event);
}
