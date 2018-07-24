/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2018/07/22 15:15:47 by adleau           ###   ########.fr       */
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

static void		__attribute__((unused))init_rt(int ac, char **__attribute__((unused))av)
{
	t_point			p;

	if (ac == 1)
		usage("Error : argument missing.", 1);
	else if (ac > 2)
		usage("Error : too many arguments.", 1);
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
	if (parse(av[1]) == false)
		usage("Error : invalid argument.", 1);
}

void			init_global(int ac, char **av)
{
	(void)ac;
	(void)av;
//	ft_putendl("debug1");
	g_global.drawn = 1;
//	init_sdl_wrap(&(g_global.sdl_mgr));
	init_gtk(ac, av);
//	init_rt(ac, av);
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

//	build_ui();

/*	while (g_global.running)
	{
		if (g_global.drawn == 1)
			draw_func();
		if (SDL_PollEvent(&(EVENT_PTR)))
		{
			if (EVENT_PTR.type == SDL_QUIT || (EVENT_PTR.type == SDL_KEYDOWN && EVENT_PTR.key.keysym.sym == SDLK_ESCAPE))
				exit(1);
//			else if (EVENT_PTR.type == SDL_KEYDOWN)
//				keyup_events_w3d(wolf);
		}

		}*/
	// getting scenes
/*  init_glfw();
// initializing glfw
// prepare opencl for parallel computing
// launch rays

while( glfwGetKey(g_global.gl_mgr.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(g_global.gl_mgr.window) == 0 )
{
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT); // important, else everything drawn will be saved onto the buffer and remain from one program exec to the other
draw();
// Swap buffers
glfwSwapBuffers(g_global.gl_mgr.window);
glfwPollEvents();
}
// free everything that was allocated
destroy_glfw();*/
	return (0);
}
