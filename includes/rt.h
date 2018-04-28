/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:49:17 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:58:49 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RT_H
# define	RT_H
# define GLFW_INCLUDE_GL3
# define GLFW_NO_GLU
# include <glfw3.h>
# if defined(__APPLE__) || defined(__MACOSX)
# include <OpenCL/opencl.h>
# else
# include <CL/cl.h>
# endif
# include <objects/optics.h>

typedef struct		s_rt
{
	t_rpoint		cam_position;
	double			screen_distance;
	t_ray			rays[WIN_H][WIN_W];
	t_obj			*objects;
	t_light			*lights;
}					t_rt;


#endif
