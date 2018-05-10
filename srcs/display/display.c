/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/05/05 14:20:28 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <thread/thread.h>
#include <rt.h>
#include <sdl_stuff/sdl_mgr.h>
#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>
#include <geometry/geometry.h>

extern t_global	g_global;

static void		*draw_image_core(void *arg)
{
	t_thread	th;
	t_sdl_wrapper		*e;
	t_point		p;
	t_rt		*r;
	t_collision	tmp;

	th = *((t_thread *)arg);
	e = th.e;
	r = &g_global.r;
	p.x = th.th_index;
	while (p.x < WIN_W)
	{
		p.y = -1;
		if (th.th_index == 0)
		{
			ft_putnbr(p.x);
			ft_putstr(" / ");
			ft_putnbr(WIN_W);
			ft_putstr("\n");
		}
		while (++p.y < WIN_H)
		{
			tmp = ray_tracing(r, r->rays[p.y][p.x]);
			if (tmp.o != NULL)
				draw_px(e->surf, p.x, p.y,		\
				get_ray_color(r, tmp));
			else
				draw_px(e->surf, p.x, p.y, ft_rgb(0, 0, 0, 0));
		}
		p.x = p.x + THREADS_NB;
	}
	pthread_exit(NULL);
}

void			draw_image(t_sdl_wrapper *e)
{
	pthread_t	threads[THREADS_NB];
	t_thread	th_arg[THREADS_NB];
	int			i;

	i = 0;
	while (i < THREADS_NB)
	{
		th_arg[i].e = e;
		th_arg[i].th_index = i;
		if (pthread_create(&(threads[i]), NULL, draw_image_core, \
			&th_arg[i]) != 0)
			ft_exit("Thread could not be created.", 1);
		i++;
	}
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			ft_exit("Thread could not be joined.", 1);
	}
	g_global.drawn = 0;
}
