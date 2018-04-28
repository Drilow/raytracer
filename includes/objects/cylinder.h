/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:49:50 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 20:06:15 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include <stdbool.h>

typedef struct		s_cylinder
{
	t_rpoint		summit;
	t_rpoint		vector;
	double			radius;
	bool			infinite;
}					t_cylinder;

bool			get_cylinder(char *s, t_cylinder *c, int *index);
t_rpoint		get_cyc_eq_factors(t_ray ray, t_cylinder *c);

#endif
