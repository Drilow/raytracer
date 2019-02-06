/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:24:04 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:23:59 by adleau           ###   ########.fr       */
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
	if (g_global.r.checker)
	{
		while (++y < WIN_H)
		{
			free(g_global.r.checker[y]);
			g_global.r.checker[y] = NULL;
		}
		free(g_global.r.checker);
		g_global.r.checker = NULL;
	}
}

void				exit_properly(int ret)
{
	if (g_global.r.objects)
		free_objects(g_global.r.objects);
	if (g_global.r.lights)
		free_lights(g_global.r.lights);
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.scene_view.win);
	free(g_global.r.gtk_mgr.pixmap);
	g_global.r.gtk_mgr.pixmap = NULL;
	free(g_global.r.gtk_mgr.saved);
	free(g_global.r.gtk_mgr.buf);
	g_global.r.gtk_mgr.saved = NULL;
	g_global.r.gtk_mgr.buf = NULL;
	free_checker();
	gtk_main_quit();
	exit(ret);
}
