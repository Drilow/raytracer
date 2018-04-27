/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_collision_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:32:55 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/02 20:37:10 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_bool	base_collision(t_ray ray, t_cone *c, t_rpoint *p)
{
	t_rpoint	bcenter;
	double		bradius;
	t_plane		pl;
	t_rpoint	pcol;

	bcenter.x = c->summit.x + c->vector.x;
	bcenter.y = c->summit.y + c->vector.y;
	bcenter.z = c->summit.z + c->vector.z;
	bradius = vlength(c->vector) * tan(c->angle);
	pl.vector = c->vector;
	pl.p = bcenter;
	if (plane_collision(ray, &pl, &pcol) == false)
		return (false);
	if (deltasq(bcenter, pcol) > (bradius * bradius))
		return (false);
	*p = pcol;
	return (true);
}

static t_bool	check_solutions(t_ray ray, t_cone *c, t_dpoint *solutions)
{
	t_rpoint	tmp1;
	t_rpoint	tmp2;
	double		max;

	max = vlength(c->vector) / cos(c->angle);
	if (c->infinite == true)
		return (true);
	tmp1 = get_vector(c->summit, new_point(ray.p, ray.vector, solutions->x));
	tmp2 = get_vector(c->summit, new_point(ray.p, ray.vector, solutions->y));
	if (vangle(c->vector, tmp1) >= (PI / 2) || vlength(tmp1) > max)
	{
		if (vangle(c->vector, tmp2) >= (PI / 2) || vlength(tmp2) > max)
			return (false);
		solutions->x = solutions->y;
	}
	else
	{
		if (vangle(c->vector, tmp2) >= (PI / 2) || vlength(tmp2) > max)
			solutions->y = solutions->x;
	}
	return (true);
}

t_bool			cone_collision(t_ray ray, t_cone *c, t_rpoint *p)
{
	t_rpoint	bcollision;
	t_rpoint	eq_factors;
	t_dpoint	solutions;

	if (get_cc_eq_factors(ray, c, &eq_factors) == false)
		return (false);
	if (find_collisions(eq_factors, &solutions) == false)
		return (false);
	if (check_solutions(ray, c, &solutions) == false)
		return (false);
	*p = closer(ray.p, new_point(ray.p, ray.vector, solutions.x), \
	new_point(ray.p, ray.vector, solutions.y));
	if (c->infinite == false && base_collision(ray, c, &bcollision) == true)
		*p = closer(ray.p, *p, bcollision);
	return (true);
}
