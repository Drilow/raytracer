/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2019/01/15 04:31:21 by Dagnear          ###   ########.fr       */
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

extern t_global		g_global;

static void		draw_image_core2(t_point p, t_rt *r)
{
	t_collision *tmp;

	while (++p.y < WIN_H)
	{
		tmp = ray_tracing(r, g_global.r->rays[p.y][p.x], REFLEX_DEPTH);
		if (tmp != NULL && tmp->o != NULL)
		{
			g_global.r->checker[p.y][p.x] = tmp->o;
			draw_px(GTKMGR.buf, p.x, p.y, \
						get_ray_color(r, tmp));
		}
		else
		{
			g_global.r->checker[p.y][p.x] = NULL;
			draw_px(GTKMGR.buf, p.x, p.y, ft_rgb(0, 0, 0, 0));
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
