/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/30 18:42:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt.h>
#include <thread/thread.h>
#include <global.h>
#define PROGRESS_DATA g_global.r->gtk_mgr.ui.progress_data

extern t_global				g_global;

gboolean		update_progress(void)
{
	gdouble		fraction;
	int			pct;
	char		*tmp;

	if (PROGRESS_DATA.len > 0)
	{
		fraction = (gfloat)PROGRESS_DATA.pos / (gfloat)PROGRESS_DATA.len;
		pct = fraction * 100;
		if (PROGRESS_DATA.nLastPct != pct)
		{
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar),
							fraction);
			tmp = ft_itoa(pct);
			tmp = ft_strmerge(" %", tmp, 2, 2);
			gtk_progress_bar_set_text(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar),
				tmp);
			free(tmp);
			while (gtk_events_pending())
				gtk_main_iteration();
			PROGRESS_DATA.nLastPct = pct;
		}
	}
	if (PROGRESS_DATA.nLastPct >= 100)
		return (TRUE);
	return (FALSE);
}

static void		end_progress(void)
{
	PROGRESS_DATA.bProgressUp = FALSE;
	gtk_widget_destroy(GTK_WIDGET(PROGRESS_DATA.window));
	pthread_mutex_destroy(&PROGRESS_DATA.g_mutex);
	pthread_cond_destroy(&PROGRESS_DATA.g_cond_a);
	pthread_cond_destroy(&PROGRESS_DATA.g_cond_b);
}

void			progress_bar(void)
{
	PROGRESS_DATA.g_state = STATE_A;
	pthread_mutex_init(&PROGRESS_DATA.g_mutex, NULL);
	pthread_cond_init(&PROGRESS_DATA.g_cond_a, NULL);
	pthread_cond_init(&PROGRESS_DATA.g_cond_b, NULL);
	PROGRESS_DATA.nLastPct = -1;
	PROGRESS_DATA.bProgressUp = TRUE;
	PROGRESS_DATA.pbar = NULL;
	PROGRESS_DATA.window = NULL;
	PROGRESS_DATA.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(PROGRESS_DATA.window), "Loading");
	gtk_window_set_position(GTK_WINDOW(PROGRESS_DATA.window),
		GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(PROGRESS_DATA.window), 220, 20);
	PROGRESS_DATA.pbar = gtk_progress_bar_new();
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar), TRUE);
	gtk_container_add(GTK_CONTAINER(PROGRESS_DATA.window), PROGRESS_DATA.pbar);
	gtk_widget_show_all(PROGRESS_DATA.window);
}

void			progress_thread_handler(gdouble x)
{
	pthread_mutex_lock(&PROGRESS_DATA.g_mutex);
	while (PROGRESS_DATA.g_state != STATE_B)
		pthread_cond_wait(&PROGRESS_DATA.g_cond_b, &PROGRESS_DATA.g_mutex);
	pthread_mutex_unlock(&PROGRESS_DATA.g_mutex);
	PROGRESS_DATA.pos = x;
	PROGRESS_DATA.len = WIN_W;
	pthread_mutex_lock(&PROGRESS_DATA.g_mutex);
	PROGRESS_DATA.g_state = STATE_A;
	pthread_cond_signal(&PROGRESS_DATA.g_cond_a);
	pthread_mutex_unlock(&PROGRESS_DATA.g_mutex);
}

void			progress_main_handler(void)
{
	bool		b_lock;

	b_lock = FALSE;
	while (b_lock == FALSE)
	{
		pthread_mutex_lock(&PROGRESS_DATA.g_mutex);
		while (PROGRESS_DATA.g_state != STATE_A)
			pthread_cond_wait(&PROGRESS_DATA.g_cond_a, &PROGRESS_DATA.g_mutex);
		pthread_mutex_unlock(&PROGRESS_DATA.g_mutex);
		b_lock = update_progress();
		if (b_lock == FALSE)
		{
			pthread_mutex_lock(&PROGRESS_DATA.g_mutex);
			while (gtk_events_pending())
				gtk_main_iteration();
			PROGRESS_DATA.g_state = STATE_B;
			pthread_cond_signal(&PROGRESS_DATA.g_cond_b);
			pthread_mutex_unlock(&PROGRESS_DATA.g_mutex);
		}
	}
	end_progress();
}
