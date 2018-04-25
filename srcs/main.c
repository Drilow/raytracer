/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2018/04/25 17:05:12 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <gl_handling/gl_includes.h>
#include <objects/object.h>
#include <global.h>

t_global		g_global;

void			draw(void)
{
	glBegin(GL_POINTS);              // Each set of 4 vertices form a quad
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(0.3, 0.3); // 0.0, 0.0 is the center of the window, -1, -1 top left corner etc
	glEnd();

	glFlush();  // Render now
}

int				main(int __attribute__((unused))ac, char __attribute__((unused))**av)
{
	// getting scenes
	init_glfw();
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
	destroy_glfw();
	return (0);
}
