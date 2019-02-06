/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:23:05 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread/thread.h>
#include <rt.h>
#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>
#include <display/display.h>

extern t_global		g_global;

static void		draw_image_core2(t_point p, t_rt *r)
{
	t_collision *tmp;

	while (++p.y < WIN_H)
	{
		tmp = ray_tracing(r, g_global.r.rays[p.y][p.x], REFLEX_DEPTH);
		if (tmp != NULL && tmp->o != NULL)
		{
			g_global.r.checker[p.y][p.x] = tmp->o;
			draw_px(g_global.r.gtk_mgr.buf, p.x, p.y, \
						get_ray_color(r, tmp));
		}
		else
		{
			g_global.r.checker[p.y][p.x] = NULL;
			draw_px(g_global.r.gtk_mgr.buf, p.x, p.y, ft_rgb(0, 0, 0, 0));
		}
		free_collisions(tmp);
	}
}

static void		*draw_image_core(void *arg)
{
	t_thread	th;
	t_point		p;
	t_rt		*r;

	th = *((t_thread *)arg);
	r = &(g_global.r);
	p.x = th.th_index;
	while (p.x < WIN_W)
	{
		p.y = -1;
		if (th.th_index == 0)
			progress_thread_handler(p.x);
		draw_image_core2(p, r);
		p.x = p.x + THREADS_NB;
	}
	if (p.x == WIN_W)
		progress_thread_handler(p.x);
	pthread_exit(NULL);
}

unsigned char	*ft_ustrdup(unsigned char *s, int size)
{
	int				i;
	unsigned char	*ret;

	i = -1;
	if (!(ret = (unsigned char*)malloc(sizeof(unsigned char) * size)))
		return (NULL);
	while (++i < size)
	{
		ret[i] = s[i];
	}
	return (ret);
}

static void		draw_image_init(int *i)
{
	*i = 0;
	if ((g_global.r.gtk_mgr.saved))
	{
		free(g_global.r.gtk_mgr.saved);
		g_global.r.gtk_mgr.saved = NULL;
	}
	progress_bar();
	g_global.r.gtk_mgr.ui.progress_data.pos = 0;
	g_global.r.gtk_mgr.ui.progress_data.len = WIN_W;
}

void			draw_image(void)
{
	pthread_t	th[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;

	draw_image_init(&i);
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
	antialiasing();
	if (!g_global.r.gtk_mgr.saved)
		if (!(g_global.r.gtk_mgr.saved = ft_ustrdup(g_global.r.gtk_mgr.buf, \
			WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
			exit_properly(1);
	g_global.drawn = 0;
}
