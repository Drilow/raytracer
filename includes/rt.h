/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:49:17 by adleau            #+#    #+#             */
/*   Updated: 2018/04/18 15:50:58 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RT_H
# define	RT_H
# define GLFW_INCLUDE_GL3
# define GLFW_NO_GLU
#include <glfw3.h>
#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#endif
