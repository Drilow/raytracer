/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/15 20:05:40 by Dagnear          ###   ########.fr       */
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

extern t_global	g_global;
enum state 			state = STATE_A;
pthread_mutex_t 	mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      condA = PTHREAD_COND_INITIALIZER;
pthread_cond_t      condB = PTHREAD_COND_INITIALIZER;

static void		draw_image_core2(t_point p, t_rt *r)
{
	t_collision tmp;

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
}

static void		*draw_image_core(void *arg)
{
	t_thread	th;
	t_point		p;
	t_rt		*r;
//	t_rgb		tmpclr;

	th = *((t_thread *)arg);
	r = g_global.r;
	p.x = th.th_index;
	while (p.x < WIN_W)
	{
		p.y = -1;
		if (th.th_index == 0)
			progress_thread_handler(p.x);
		draw_image_core2(p, r);
		p.x = p.x + THREADS_NB;
	}
	if(p.x == WIN_W)
		progress_thread_handler(p.x);
	pthread_exit(NULL);
}

void			draw_image(void)
{
	pthread_t	th[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;

	i = 0;
	progress_bar();
	PROGRESS_DATA.pos = 0;
	PROGRESS_DATA.len = WIN_W;
	while (i < THREADS_NB)
	{
		th_arg[i].th_index = i;
		if (pthread_create(&(th[i]), NULL, draw_image_core, &th_arg[i]) != 0)
			ft_exit("Thread could not be created.", 1);
		i++;
	}
	progress_main_handler();
	while (i > 0)
	{
		i--;
		if (pthread_join(th[i], NULL) != 0)
			ft_exit("Thread could not be joined.", 1);
	}
	if (ANTIALIASING == 1)
		antialiasing();
	g_global.drawn = 0;
}
