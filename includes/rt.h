/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:49:17 by adleau            #+#    #+#             */
/*   Updated: 2018/05/10 11:59:17 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RT_H
# define	RT_H
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
