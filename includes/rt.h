/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:49:17 by adleau            #+#    #+#             */
/*   Updated: 2018/05/05 13:18:51 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RT_H
# define	RT_H
# if defined(__APPLE__) || defined(__MACOSX)
# include <OpenCL/opencl.h>
# else
# include <CL/cl.h>
# endif
# include <objects/object.h>
# include <geometry/geometry.h>
# include <sdl_stuff/sdl_mgr.h>

typedef struct		s_rt
{
	t_rpoint		cam_position;
	double			screen_distance;
	t_ray			rays[WIN_H][WIN_W];
	t_obj			*objects;
	t_light			*lights;
}					t_rt;


#endif
