/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2019/01/25 15:22:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <global.h>
#include <geometry/geometry.h>
#include <extra/extra_defs.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>

t_global		g_global;

void				ft_exit(char *msg_error, int i)
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

void				init_obj_tab(void)
{
	int			y;

	y = -1;
	g_global.r.checker = NULL;
	if (!(g_global.r.checker = malloc(sizeof(t_obj**) * WIN_H)))
		exit(1);
	while (++y < WIN_H)
	{
		g_global.r.checker[y] = NULL;
		if (!(g_global.r.checker[y] = malloc(sizeof(t_obj*) * WIN_W)))
			exit(1);
	}
}

void				init_rt(void)
{
	t_point			p;

	init_obj_tab();
	PIXMAP = NULL;
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

int					main(int ac, char **av)
{
	g_global.drawn = 1;
	init_gtk(ac, av);
	return (0);
}
