/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:49:17 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 16:10:10 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <objects/object.h>
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
}					t_rt;

#endif
