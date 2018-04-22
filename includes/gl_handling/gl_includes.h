/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_includes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:58:26 by adleau            #+#    #+#             */
/*   Updated: 2018/04/22 16:09:09 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_INCLUDES_H
# define GL_INCLUDES_H
# define GLFW_INCLUDE_GL3  /* don't drag in legacy GL headers. */
# define GLFW_NO_GLU       /* don't drag in the old GLU lib - unless you must. */
# include <glfw3.h>      /* simple and easy to use. omit legacy GL. */
# include <OpenGL/OpenGL.h>
# include <OpenGL/gl.h>
# include <OpenGL/CGLDevice.h>
# include <OpenCL/opencl.h>

typedef struct	s_gl_mgr
{

}				t_gl_mgr;

void			init_glfw(void);

#endif
