/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2018/08/07 08:58:33 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <objects/object.h>
#include <global.h>
#include <cl_inc/cl_defs.h>
#include <geometry/geometry.h>
#include <extra/extra_defs.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#include <sdl_stuff/sdl_mgr.h>
#define EVENT_PTR g_global.sdl_mgr.event

t_global		g_global;

void	ft_exit(char *msg_error, int i)
{
	if (msg_error != NULL)
	{
		ft_putstr(msg_error);
		ft_putstr("\n");
	}
	exit(i);
}

static void			init_ray(t_point p)
{
	g_global.r.rays[p.y][p.x].p = g_global.r.cam_position;
	g_global.r.rays[p.y][p.x].vector.x = p.x - (WIN_W / 2);
	g_global.r.rays[p.y][p.x].vector.y = -p.y + (WIN_H / 2);
	g_global.r.rays[p.y][p.x].vector.z = g_global.r.screen_distance;
}

static void		__attribute__((unused))init_rt(int __attribute__((unused))ac, char **__attribute__((unused))av)
{
	t_point			p;

	g_global.r.cam_position.x = 0;
	g_global.r.cam_position.y = 0;
	g_global.r.cam_position.z = 0;
	g_global.r.screen_distance = (WIN_W / 2) / tan(FOV / 2);
	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
			init_ray(p);
	}
}

void			init_global(int ac, char **av)
{
//	ft_putendl("debug1");
	g_global.drawn = 1;
	init_rt(ac, av);
	init_sdl_wrap(&(g_global.sdl_mgr));
	init_gtk(ac, av);
	g_global.running = 1;
}

void			draw_func(void)
{
	sdl_loop_init();
	// code
	draw_image(&(g_global.sdl_mgr));
	sdl_loop_end();
}


int				main(int __attribute__((unused))ac, char __attribute__((unused))**av)
{
	init_global(ac, av);
	return (0);
}
