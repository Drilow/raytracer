/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:24:04 by adleau            #+#    #+#             */
/*   Updated: 2019/01/14 13:40:24 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global g_global;

void				exit_callback(void)
{
	exit_properly(0);
}

void				exit_properly(int ret)
{
	if (g_global.r && g_global.r->objects)
		free_objects(g_global.r->objects);
	if (g_global.r && g_global.r->lights)
		free_lights(g_global.r->lights);
	gtk_widget_destroy(SCENE_VIEW.win);
	free(PIXMAP);
	PIXMAP = NULL;
	free(GTKMGR.saved);
	free(GTKMGR.buf);
	GTKMGR.saved = NULL;
	GTKMGR.buf = NULL;
// free everything in g_global.r
	free(g_global.r);
	g_global.r = NULL;
	gtk_main_quit();
	exit(ret);
}
