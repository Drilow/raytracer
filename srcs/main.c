/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2018/04/22 16:39:17 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <gl_handling/gl_includes.h>
#include <objects/object.h>
#include <global.h>

t_global		g_global;

int				main(int __attribute__((unused))ac, char __attribute__((unused))**av)
{
	// getting scenes
	init_glfw();
	// initializing glfw
	// prepare opencl for parallel computing
	// launch rays
	// trace (glfw loop)
	while (!glfwWindowShouldClose(g_global.gl_mgr.window))
	{
		// Keep running
	}
	// free everything that was allocated
	return (0);
}
