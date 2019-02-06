/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:51:19 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global				g_global;

gboolean		update_progress(void)
{
	gdouble		fraction;
	int			pct;

	if (g_global.r.gtk_mgr.ui.progress_data.len <= 0)
		return (TRUE);
	fraction = (gfloat)g_global.r.gtk_mgr.ui.progress_data.pos
	/ (gfloat)g_global.r.gtk_mgr.ui.progress_data.len;
	pct = fraction * 100;
	if (g_global.r.gtk_mgr.ui.progress_data.nlastpct != pct)
	{
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(
		g_global.r.gtk_mgr.ui.progress_data.pbar), fraction);
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(
		g_global.r.gtk_mgr.ui.progress_data.pbar), NULL);
		while (gtk_events_pending())
			gtk_main_iteration();
		g_global.r.gtk_mgr.ui.progress_data.nlastpct = pct;
	}
	if (g_global.r.gtk_mgr.ui.progress_data.nlastpct >= 100)
		return (TRUE);
	return (FALSE);
}

static void		end_progress(void)
{
	g_global.r.gtk_mgr.ui.progress_data.bprogressup = FALSE;
	gtk_widget_destroy(
	GTK_WIDGET(g_global.r.gtk_mgr.ui.progress_data.window));
	g_global.r.gtk_mgr.ui.progress_data.window = NULL;
	pthread_mutex_destroy(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
	pthread_cond_destroy(&g_global.r.gtk_mgr.ui.progress_data.g_cond_a);
	pthread_cond_destroy(&g_global.r.gtk_mgr.ui.progress_data.g_cond_b);
}

void			progress_bar(void)
{
	progress_bar_init();
	gtk_window_set_transient_for(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.progress_data.window),
	GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win));
	gtk_window_set_destroy_with_parent(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.progress_data.window), TRUE);
	gtk_window_set_title(GTK_WINDOW(g_global.r.gtk_mgr.ui.progress_data.window),
	"Loading");
	gtk_window_set_position(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.progress_data.window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.progress_data.window), 220, 20);
	g_global.r.gtk_mgr.ui.progress_data.pbar = gtk_progress_bar_new();
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(
	g_global.r.gtk_mgr.ui.progress_data.pbar), TRUE);
	gtk_window_set_deletable(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.progress_data.window), FALSE);
	gtk_window_set_resizable(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.progress_data.window), FALSE);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.progress_data.window),
	g_global.r.gtk_mgr.ui.progress_data.pbar);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.progress_data.window);
}

void			progress_thread_handler(gdouble x)
{
	pthread_mutex_lock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
	while (g_global.r.gtk_mgr.ui.progress_data.g_state != STATE_B)
		pthread_cond_wait(&g_global.r.gtk_mgr.ui.progress_data.g_cond_b,
		&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
	pthread_mutex_unlock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
	g_global.r.gtk_mgr.ui.progress_data.pos = x;
	g_global.r.gtk_mgr.ui.progress_data.len = WIN_W;
	pthread_mutex_lock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
	g_global.r.gtk_mgr.ui.progress_data.g_state = STATE_A;
	pthread_cond_signal(&g_global.r.gtk_mgr.ui.progress_data.g_cond_a);
	pthread_mutex_unlock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
}

void			progress_main_handler(void)
{
	bool		b_lock;

	b_lock = FALSE;
	while (b_lock == FALSE)
	{
		pthread_mutex_lock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
		while (g_global.r.gtk_mgr.ui.progress_data.g_state != STATE_A)
			pthread_cond_wait(&g_global.r.gtk_mgr.ui.progress_data.g_cond_a,
			&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
		pthread_mutex_unlock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
		b_lock = update_progress();
		if (b_lock == FALSE)
		{
			pthread_mutex_lock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
			while (gtk_events_pending())
				gtk_main_iteration();
			g_global.r.gtk_mgr.ui.progress_data.g_state = STATE_B;
			pthread_cond_signal(&g_global.r.gtk_mgr.ui.progress_data.g_cond_b);
			pthread_mutex_unlock(&g_global.r.gtk_mgr.ui.progress_data.g_mutex);
		}
	}
	end_progress();
}
