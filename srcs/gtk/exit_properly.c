/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:24:04 by adleau            #+#    #+#             */
/*   Updated: 2019/01/15 03:59:12 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global g_global;

void				exit_callback(void)
{
	exit_properly(0);
}

void				free_checker(void)
{
	int				y;

	y = -1;
	if (g_global.r->checker)
	{
		while(++y < WIN_H)
		{
			free(g_global.r->checker[y]);
			g_global.r->checker[y] = NULL;
		}
		free(g_global.r->checker);
		g_global.r->checker= NULL;
		free(g_global.r->selected_obj);
		g_global.r->selected_obj = NULL;
	}
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
	free_checker();
	//if (ADD_VIEW.sw.o)
	//	free(ADD_VIEW.sw.o);
	free(g_global.r);
	g_global.r = NULL;
	gtk_main_quit();
	exit(ret);
}