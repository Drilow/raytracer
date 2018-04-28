/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:52:59 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:50:43 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include <stddef.h>
# include "solid_object.h"

typedef struct		s_sphere
{
	t_rpoint		center;
	double			radius;
}					t_sphere;

#endif
