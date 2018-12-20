/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:27:04 by adleau            #+#    #+#             */
/*   Updated: 2018/11/07 16:10:53 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H


bool			set_camera(t_rpoint angle);
bool			find_collisions(t_rpoint factors, t_dpoint *solutions, double minimum);
t_ray			get_ray(t_rpoint p, t_rpoint vector);

#endif
