/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:04:21 by adleau            #+#    #+#             */
/*   Updated: 2018/04/22 16:41:20 by adleau           ###   ########.fr       */
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

	if (!glfwInit())
		exit(1);
	g_global.gl_mgr.window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!g_global.gl_mgr.window)
	{
		ft_putstr_fd("Failed to create window.\n", 2);
		exit(1);
	}
	glfwMakeContextCurrent(g_global.gl_mgr.window);
}
