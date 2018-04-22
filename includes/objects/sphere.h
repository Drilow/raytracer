/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:52:59 by adleau            #+#    #+#             */
/*   Updated: 2018/04/22 14:53:12 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include <stddef.h>
# include "solid_object.h"

union u_solid_object_wrapper;
struct s_string;

typedef struct		s_sphere
{
	t_solid_object	base_object;
	double			ray;
}					t_sphere;

char			init_sphere(
	union u_solid_object_wrapper *const object_wrapper,
	const struct s_string *datas);

#endif
