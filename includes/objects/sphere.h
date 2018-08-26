/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:52:59 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 17:01:46 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include <stddef.h>
# include <stdbool.h>
# include <objects/object.h>

typedef struct		s_sphere
{
	t_rpoint		center;
	double			radius;
}					t_sphere;

bool				get_sphere(char *s, t_obj *o, int *index);
bool				sphere_collision(t_ray ray, t_sphere *s, t_rpoint *p);

#endif
