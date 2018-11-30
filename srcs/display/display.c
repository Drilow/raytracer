/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/30 18:56:21 by adleau           ###   ########.fr       */
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

extern t_global		g_global;
enum state 			g_state = STATE_A;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      g_cond_a = PTHREAD_COND_INITIALIZER;
pthread_cond_t      g_cond_b = PTHREAD_COND_INITIALIZER;

static void		draw_image_core2(t_point p, t_rt *r)
{
	t_collision *tmp;

	while (++p.y < WIN_H)
	{
//		g_global.r->checker[p.y][p.x] = NULL;
//		if (p.x > 376 && p.x % THREADS_NB == 0)
		tmp = ray_tracing(r, g_global.r->rays[p.y][p.x]);
//		draw_px(GTKMGR.buf, p.x, p.y,			\
//				get_ray_color(r, tmp, false));
//		if (tmp != NULL)
//			g_global.r->checker[p.y][p.x] = tmp->o;
//		if (p.x > 376 && p.x % THREADS_NB == 0)
		if (tmp->o != NULL)
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
//			if (p.x > 376 && p.x % THREADS_NB == 0)
			g_global.r->checker[p.y][p.x] = tmp->o;
//			if (p.x > 376 && p.x % THREADS_NB == 0)
			draw_px(GTKMGR.buf, p.x, p.y, \
						get_ray_color(r, tmp));
//			if (p.x > 376 && p.x % THREADS_NB == 0)
//				get_ray_color(r, tmp.o, tmp.p));
		}
		else
		{
//			if (p.x > 376 && p.x % THREADS_NB == 0)
			g_global.r->checker[p.y][p.x] = NULL;
//				if (p.y > 120)
//					printf("Black pixel : x=%d & y=%d\n", p.x, p.y);
//			if (p.x > 376 && p.x % THREADS_NB == 0)
			draw_px(GTKMGR.buf, p.x, p.y, ft_rgb(0, 0, 0, 0));
//			if (p.x > 376 && p.x % THREADS_NB == 0)
		}
//		if (p.x > 376 && p.x % THREADS_NB == 0)
		free_collisions(tmp);
//		if (p.x > 376 && p.x % THREADS_NB == 0)
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

unsigned char		*ft_ustrdup(unsigned char *s, int size)
{
	int				i;
	unsigned char	*ret;

	i = -1;
	if (!(ret = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1))))
		return (NULL);
	while (++i < size)
	{
		ret[i] = s[i];
	}
	return (ret);
}

void			draw_image(void)
{
	pthread_t	th[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;

	if ((GTKMGR.saved))
	{
		free(GTKMGR.saved);
		GTKMGR.saved = NULL;
	}
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
	if (!(GTKMGR.saved = ft_ustrdup(GTKMGR.buf, WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
		exit(1); //fix
	g_global.drawn = 0;
}
