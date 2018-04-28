/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:11:16 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/27 17:36:13 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_rpoint		get_eq_factors(t_ray ray, t_sphere *sph)
{
	t_rpoint		f;
	t_rpoint		v;
	t_rpoint		c;
	t_rpoint		s;
	double			rad;

	v = ray.vector;
	c = ray.p;
	s = sph->center;
	rad = sph->radius;
	f.x = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	f.y = ((2 * v.x) * (c.x - s.x)) + ((2 * v.y) * (c.y - s.y)) \
	+ ((2 * v.z) * (c.z - s.z));
	f.z = (c.x * c.x) + (s.x * s.x) + (c.y * c.y) + (s.y * s.y) \
	+ (c.z * c.z) + (s.z * s.z) \
	- (2 * ((c.x * s.x) + (c.y * s.y) + (c.z * s.z))) \
	- (rad * rad);
	return (f);
}

t_bool				sphere_collision(t_ray ray, t_sphere *s, t_rpoint *p)
{
	t_dpoint		solutions;
	t_rpoint		eq_factors;

	eq_factors = get_eq_factors(ray, s);
	if (ft_solve_equation(eq_factors, &solutions) == false)
		return (false);
	if (solutions.x < 0)
	{
		if (solutions.y < 0)
			return (false);
		solutions.x = solutions.y;
	}
	else if (solutions.y < 0)
		solutions.y = solutions.x;
	*p = closer(ray.p, new_point(ray.p, ray.vector, solutions.x), \
		new_point(ray.p, ray.vector, solutions.y));
	return (true);
}