/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 13:25:48 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/02 20:41:07 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		*draw_image_core(void *arg)
{
	t_thread	th;
	t_env		*e;
	t_point		p;
	t_rtv1		*r;
	t_collision	tmp;

	th = *((t_thread *)arg);
	e = th.e;
	r = (t_rtv1 *)e->data;
	p.x = th.th_index;
	while (p.x < WIN_SIZE_X)
	{
		p.y = -1;
		while (++p.y < WIN_SIZE_Y)
		{
			tmp = ray_tracing(r, r->rays[p.y][p.x]);
			if (tmp.o != NULL)
				ftx_img_pixel_put(e->i, p.x, p.y, \
				get_ray_color(r, tmp.o, tmp.p));
			else
				ftx_img_pixel_put(e->i, p.x, p.y, ft_rgb(0, 0, 0, 0));
		}
		p.x = p.x + THREADS_NB;
	}
	pthread_exit(NULL);
}

void			draw_image(t_env *e)
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
			ft_exit("Thread could not be created.");
		i++;
	}
	while (i > 0)
	{
		i--;
		if (pthread_join(threads[i], NULL) != 0)
			ft_exit("Thread could not be joined.");
	}
}
