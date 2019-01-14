/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2019/01/14 03:13:26 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <global.h>
#include <geometry/geometry.h>
#include <extra/extra_defs.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
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
	g_global.r->rays[p.y][p.x].p = g_global.r->cam_position;
	g_global.r->rays[p.y][p.x].vector.x = p.x - (WIN_W / 2);
	g_global.r->rays[p.y][p.x].vector.y = -p.y + (WIN_H / 2);
	g_global.r->rays[p.y][p.x].vector.z = g_global.r->screen_distance;
}

void			setup_rt_lst(void)
{
	if (!(g_global.r = (t_rt*)malloc(sizeof(t_rt))))
		exit(1);
	g_global.r->checker = NULL;
	g_global.r->selected_obj = NULL;
	g_global.r->objects = NULL;
	g_global.r->lights = NULL;
	g_global.r->next = NULL;
	g_global.first_scene = g_global.r;
}

void			add_link_to_rt_list(void)
{
	t_rt		*tmp;

	if (!(tmp = (t_rt*)malloc(sizeof(t_rt))))
		exit(1);
	g_global.r->next = tmp;
	g_global.r = g_global.r->next;
}

void			init_obj_tab(void)
{
	int			y;

	y = -1;
	g_global.r->checker = NULL;
	if (!(g_global.r->checker = malloc(sizeof(t_obj**) * WIN_H)))
		exit(1);
	while (++y < WIN_H)
		if (!(g_global.r->checker[y] = malloc(sizeof(t_obj*) * WIN_W)))
			exit(1);
}

void			init_rt(void)
{
	t_point			p;

	if (g_global.r == NULL)
		setup_rt_lst();
	else
		add_link_to_rt_list();
	init_obj_tab();
	PIXMAP = NULL;
	g_global.r->cam_position.x = 0;
	g_global.r->cam_position.y = 0;
	g_global.r->cam_position.z = 0;
	g_global.r->screen_distance = (WIN_W / 2) / tan(FOV / 2);
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
	g_global.r = NULL;
	init_gtk(ac, av);
}



int				main(int __attribute__((unused))ac, char __attribute__((unused))**av)
{
	init_global(ac, av);
	return (0);
}
