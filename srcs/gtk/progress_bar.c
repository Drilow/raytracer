/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/19 15:26:01 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <thread/thread.h>
#include <global.h>
#include <libft.h>
#define PROGRESS_DATA g_global.r->gtk_mgr.ui.progress_data

extern t_global            g_global;
extern enum state          state;
extern pthread_mutex_t     mutex;
extern pthread_cond_t      condA;
extern pthread_cond_t      condB;

gboolean updateProgress()
{
    gdouble fraction;
    int pct;

    if (PROGRESS_DATA.len > 0)
    {
        fraction = (gfloat)PROGRESS_DATA.pos / (gfloat)PROGRESS_DATA.len;
        pct = fraction * 100;
        if (PROGRESS_DATA.nLastPct != pct)
        {
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar),
                               fraction);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar),
            	ft_strjoin(ft_itoa(pct), " %"));
             while (gtk_events_pending())
                 gtk_main_iteration();
            PROGRESS_DATA.nLastPct = pct;
        }
    }
    if (PROGRESS_DATA.nLastPct >= 100)
    	return(TRUE);
    return FALSE;
}

static void EndProgress ()
{
    PROGRESS_DATA.bProgressUp = FALSE;
    gtk_widget_destroy(PROGRESS_DATA.window);
}

void			progress_bar()
{
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

void		progress_thread_handler(gdouble x)
{
	pthread_mutex_lock(&mutex);
    while (state != STATE_B)
        pthread_cond_wait(&condB, &mutex);
    pthread_mutex_unlock(&mutex);
	PROGRESS_DATA.pos = x;
	PROGRESS_DATA.len = WIN_W;
	pthread_mutex_lock(&mutex);
    state = STATE_A;
    pthread_cond_signal(&condA);
    pthread_mutex_unlock(&mutex);
}

void		progress_main_handler()
{
	bool bGotSomeData;

	bGotSomeData = FALSE;
	while (bGotSomeData == FALSE)
    {
    	pthread_mutex_lock(&mutex);
        while (state != STATE_A)
            pthread_cond_wait(&condA, &mutex);
        pthread_mutex_unlock(&mutex);
        bGotSomeData = updateProgress();
        if(bGotSomeData == FALSE)
        {
        	pthread_mutex_lock(&mutex);
    	    while (gtk_events_pending())
                 gtk_main_iteration();
             state = STATE_B;
    	    pthread_cond_signal(&condB);
	        pthread_mutex_unlock(&mutex);
        }
    }
    EndProgress();
}