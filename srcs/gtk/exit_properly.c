/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:24:04 by adleau            #+#    #+#             */
/*   Updated: 2019/01/14 03:04:11 by adleau           ###   ########.fr       */
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
	gtk_main_quit();
	free(PIXMAP);
	PIXMAP = NULL;
	free(GTKMGR.saved);
	free(GTKMGR.buf);
	GTKMGR.saved = NULL;
	GTKMGR.buf = NULL;
	free(g_global.r);
	g_global.r = NULL;
	exit(ret);
}
