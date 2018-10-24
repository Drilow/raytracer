/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:01:03 by adleau            #+#    #+#             */
/*   Updated: 2018/10/24 17:48:50 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RT_H
# define	RT_H
# include <objects/object.h>
# include <geometry/geometry.h>
# include <gtk_mgr/gtk_mgr.h>
# define WIN_W 800
# define WIN_H 600


typedef struct		s_rt
{
	t_gtk_mgr		gtk_mgr;
	t_rpoint		cam_position;
	double			screen_distance;
	t_ray			rays[WIN_H][WIN_W];
	t_obj			***checker;
	t_obj			*selected_obj;
	t_obj			*objects;
	t_light			*lights;
	t_rgb			ambient_light;
	struct s_rt		*next;
}					t_rt;


#endif
