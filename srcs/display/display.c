/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/14 17:38:40 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <thread/thread.h>
#include <rt.h>
#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>
#include <geometry/geometry.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define PROGRESS_DATA g_global.r->gtk_mgr.ui.progress_data

enum { STATE_A, STATE_B }
static state = STATE_A;
static pthread_mutex_t 	mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t      condA = PTHREAD_COND_INITIALIZER;
static pthread_cond_t      condB = PTHREAD_COND_INITIALIZER;

extern t_global	g_global;

gboolean updateProgress (__attribute__((unused))gpointer user_data)
{
    gfloat pvalue;
    gdouble fraction;
    int pct;
    t_progress_data *data = &PROGRESS_DATA;

    /* --- Prevent divide by zero errors --- */
    if (data->len > 0) {
        /* --- Calculate the percentage --- */
        pvalue = (gfloat) data->pos / (gfloat) data->len;

        pct = pvalue * 100;

        if (data->nLastPct != pct)
        {
          	gtk_progress_bar_set_pulse_step (GTK_PROGRESS_BAR (data->pbar),
                                 pvalue);
			gtk_progress_bar_pulse (GTK_PROGRESS_BAR (data->pbar));
            /* --- Update the displayed value --- */
            fraction = pvalue;
            gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (data->pbar),
                               fraction);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data->pbar), ft_strjoin(ft_itoa(pct), " %"));
            /* --- Repaint any windows - like the progress bar --- */
             while (gtk_events_pending ()) {
                 gtk_main_iteration ();
             }
            data->nLastPct = pct;
        }
    }
    if (data->nLastPct >= 100)
    	return(TRUE);
    return FALSE;
}

void EndProgress ()
{
    /* --- Allow it to close --- */
    PROGRESS_DATA.bProgressUp = FALSE;

    /* --- Destroy the window --- */
    gtk_widget_destroy (PROGRESS_DATA.window);
}

void			*progress_bar()
{
    PROGRESS_DATA.nLastPct = -1;
    PROGRESS_DATA.bProgressUp = TRUE;
    PROGRESS_DATA.pbar = NULL;
    PROGRESS_DATA.window = NULL;

    PROGRESS_DATA.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (PROGRESS_DATA.window), "Loading");
    //gtk_window_set_transient_for(GTK_WINDOW(PROGRESS_DATA.window), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(PROGRESS_DATA.window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (PROGRESS_DATA.window), 220, 20);

    /* Create the GtkProgressBar */
    PROGRESS_DATA.pbar = gtk_progress_bar_new ();
    gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (PROGRESS_DATA.pbar), TRUE);
    gtk_container_add (GTK_CONTAINER(PROGRESS_DATA.window), PROGRESS_DATA.pbar);

    gtk_widget_show_all(PROGRESS_DATA.window);

    return NULL;
}

static void		*draw_image_core(void *arg)
{
	t_thread	th;
	t_point		p;
	t_rt		*r;
	t_collision	tmp;
	t_progress_data *progress;
//	t_rgb		tmpclr;

	th = *((t_thread *)arg);
	progress = th.data;
	r = g_global.r;
	p.x = th.th_index;
	while (p.x < WIN_W)
	{
		p.y = -1;

		if (th.th_index == 0)
		{
			pthread_mutex_lock(&mutex);
        while (state != STATE_B)
            pthread_cond_wait(&condB, &mutex);
        pthread_mutex_unlock(&mutex);
			 progress->pos = p.x;
		  	 progress->len = WIN_W;
			ft_putnbr(p.x);
			ft_putstr(" / ");
			ft_putnbr(WIN_W);
			ft_putstr("\n");
			pthread_mutex_lock(&mutex);
        state = STATE_A;
        pthread_cond_signal(&condA);
        pthread_mutex_unlock(&mutex);
		}

		while (++p.y < WIN_H)
		{
			tmp = ray_tracing(r, g_global.r->rays[p.y][p.x], false);
			if (tmp.o != NULL)
			{
//				if ((p.x == 361 || p.x == 360) && p.y == 209)
//				if (p.x == 360 && p.y == 209)
//					tmpclr = get_ray_color(r, tmp, true);
//				else
//					tmpclr = get_ray_color(r, tmp, false);
//				if (tmp.o->type == 2 && tmpclr.g < 50 && p.y > 200)
//				{
//					printf("incorrect pixel (%d, %d) : ", p.x, p.y);
//					printf("rgb(%d, %d, %d)\n", tmpclr.r, tmpclr.g, tmpclr.b);
//				}
//				if (p.x == 361 && p.y == 209)
//					printf("correct(361, 209) : rgb(%d, %d, %d)\n", tmpclr.r, tmpclr.g, tmpclr.b);
				g_global.r->checker[p.y][p.x] = tmp.o;
				draw_px(GTKMGR.buf, p.x, p.y, \
							get_ray_color(r, tmp, false));
//				get_ray_color(r, tmp.o, tmp.p));
			}
			else
			{
				g_global.r->checker[p.y][p.x] = NULL;
//				if (p.y > 120)
//					printf("Black pixel : x=%d & y=%d\n", p.x, p.y);
				draw_px(GTKMGR.buf, p.x, p.y, ft_rgb(0, 0, 0, 0));
			}
		}
		p.x = p.x + THREADS_NB;
	}
	if(p.x == WIN_W)
	{
		pthread_mutex_lock(&mutex);
        while (state != STATE_B)
            pthread_cond_wait(&condB, &mutex);
        pthread_mutex_unlock(&mutex);
		progress->pos = p.x;
		pthread_mutex_lock(&mutex);
        state = STATE_A;
        pthread_cond_signal(&condA);
        pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void			draw_image(void)
{
	pthread_t	threads[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;
	bool bGotSomeData;

	i = 0;
	progress_bar();
	PROGRESS_DATA.pos = 0;
	PROGRESS_DATA.len = WIN_W;
	while (i < THREADS_NB)
	{
		th_arg[i].th_index = i;
		th_arg[i].data = &PROGRESS_DATA;
		if (pthread_create(&(threads[i]), NULL, draw_image_core, \
						   &th_arg[i]) != 0)
			ft_exit("Thread could not be created.", 1);
		i++;
	}
	bGotSomeData = FALSE;
	while(bGotSomeData == FALSE)
    {
    	pthread_mutex_lock(&mutex);
        while (state != STATE_A)
            pthread_cond_wait(&condA, &mutex);
        pthread_mutex_unlock(&mutex);
        bGotSomeData = updateProgress(NULL);
        if(bGotSomeData == FALSE)
        {
        	pthread_mutex_lock(&mutex);
    	    while (gtk_events_pending ()) {
                 gtk_main_iteration ();
             }
             state = STATE_B;
    	    pthread_cond_signal(&condB);
	        pthread_mutex_unlock(&mutex);
        }
    }
    EndProgress();
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			ft_exit("Thread could not be joined.", 1);
	}
	if (ANTIALIASING == 1)
		antialiasing();
	g_global.drawn = 0;
}
