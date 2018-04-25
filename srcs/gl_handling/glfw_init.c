/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:04:21 by adleau            #+#    #+#             */
/*   Updated: 2018/04/25 15:35:45 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gl_handling/gl_includes.h>
#include <objects/object.h>
#include <libft.h>

#include <global.h>

#include <stdio.h>

extern t_global g_global;

void			init_glfw(void)
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
	if (!glfwInit())
		exit(1);
	g_global.gl_mgr.window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!g_global.gl_mgr.window)
	{
		ft_putstr_fd("Failed to create window.\n", 2);
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(g_global.gl_mgr.window);
	glewExperimental=true; // Nécessaire dans le profil de base
	if (glewInit() != GLEW_OK)
	{
		ft_putstr_fd("Failed to initialize GLEW\n", 2);
		exit(1);
	}
	glGenVertexArrays(1, &g_global.gl_mgr.vertex_array_id);
	glBindVertexArray(g_global.gl_mgr.vertex_array_id);
	glfwSetInputMode(g_global.gl_mgr.window, GLFW_STICKY_KEYS, GL_TRUE);
}
