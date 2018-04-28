/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 13:14:02 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <gl_handling/gl_includes.h>
#include <objects/object.h>
#include <global.h>
#include <cl_inc/cl_defs.h>

t_global		g_global;

void			draw(void)
{
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	glColor3f(1.0f, 0.0f, 0.0f); // Red 0.0-1.0
	glVertex2f(-0.3, -0.3);
	glVertex2f(-0.3, 0.3);
	glColor3f(0.0f, 1.0f, 0.0f); // green 0.0-1.0
	glVertex2f(0.3, 0.3);
	glVertex2f(0.3, -0.3);
	glEnd();
	glBegin(GL_TRIANGLES);              // Each set of 4 vertices form a quad
	glColor3ub(255, 255, 255); // 0-255
	glVertex2f(-0.3, -0.3);
	glVertex2f(-0.3, 0.3);
	glVertex2f(0.3, 0.3);
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
