/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_includes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:58:26 by adleau            #+#    #+#             */
/*   Updated: 2018/04/25 16:36:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_INCLUDES_H
# define GL_INCLUDES_H
# define GLFW_INCLUDE_GL3  /* don't drag in legacy GL headers. */
# define GLFW_NO_GLU       /* don't drag in the old GLU lib - unless you must. */
#include <GL/glew.h>
# include <glfw3.h>      /* simple and easy to use. omit legacy GL. */
# include <OpenGL/OpenGL.h>
# include <OpenGL/gl.h>
# include <OpenGL/CGLDevice.h>
# include <OpenCL/opencl.h>

typedef struct	s_gl_mgr
{
	GLFWwindow*	window;
	GLuint		vertex_array_id;
	GLvoid		*data;
}				t_gl_mgr;

void			init_glfw(void);
void			error_callback(int error, const char* description);
void			destroy_glfw(void);
void			draw(void);

#endif
