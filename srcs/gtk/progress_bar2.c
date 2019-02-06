/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:58:09 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global				g_global;

void						progress_bar_init(void)
{
	g_global.r.gtk_mgr.ui.progress_data.g_state = STATE_A;
	pthread_mutex_init(&g_global.r.gtk_mgr.ui.progress_data.g_mutex, NULL);
	pthread_cond_init(&g_global.r.gtk_mgr.ui.progress_data.g_cond_a, NULL);
	pthread_cond_init(&g_global.r.gtk_mgr.ui.progress_data.g_cond_b, NULL);
	g_global.r.gtk_mgr.ui.progress_data.nlastpct = -1;
	g_global.r.gtk_mgr.ui.progress_data.bprogressup = TRUE;
	g_global.r.gtk_mgr.ui.progress_data.pbar = NULL;
	g_global.r.gtk_mgr.ui.progress_data.window = NULL;
	g_global.r.gtk_mgr.ui.progress_data.window = gtk_window_new(
	GTK_WINDOW_TOPLEVEL);
}
