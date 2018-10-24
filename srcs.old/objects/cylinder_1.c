/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collision_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:33:05 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 20:03:51 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>


static bool		bc_init(t_cylinder *c, t_plane *pl1, t_plane *pl2)
{
	if (c->infinite == true)
		return (false);
	pl1->vector = c->vector;
	pl2->vector = c->vector;
	pl1->p = c->summit;
	pl2->p = set_rpoint(pl1->p.x + c->vector.x, \
	pl1->p.y + c->vector.y, pl1->p.z + c->vector.z);
	return (true);
}

static bool		base_collision(t_ray ray, t_cylinder *c, t_rpoint *bc)
{
	t_rpoint		bcol1;
	t_rpoint		bcol2;
	t_plane			pl1;
	t_plane			pl2;

	if (bc_init(c, &pl1, &pl2) == false)
		return (false);
	if (plane_collision(ray, &pl1, &bcol1) == false \
		|| deltasq(pl1.p, bcol1) > pow(c->radius, 2))
	{
		if (plane_collision(ray, &pl2, &bcol2) == false \
			|| deltasq(pl2.p, bcol2) > pow(c->radius, 2))
			return (false);
		*bc = bcol2;
		return (true);
	}
	else if (plane_collision(ray, &pl2, &bcol2) == false \
		|| deltasq(pl2.p, bcol2) > pow(c->radius, 2))
		*bc = bcol1;
	else
		*bc = closer(ray.p, bcol1, bcol2);
	return (true);
}

static bool		between_bases(t_ray ray, t_cylinder *c, t_dpoint *s)
{
	t_rpoint		p1;
	t_rpoint		p2;
	t_rpoint		ccenter;
	double			max_distance;

	if (c->infinite == true)
		return (true);
	p1 = new_point(ray.p, ray.vector, s->x);
	p2 = new_point(ray.p, ray.vector, s->y);
	ccenter.x = c->summit.x + (c->vector.x / 2);
	ccenter.y = c->summit.y + (c->vector.y / 2);
	ccenter.z = c->summit.z + (c->vector.z / 2);
	max_distance = pow(c->radius, 2) + deltasq(c->summit, ccenter);
	if (deltasq(p1, ccenter) > max_distance)
	{
		if (deltasq(p2, ccenter) > max_distance)
			return (false);
		s->x = s->y;
	}
	else if (deltasq(p2, ccenter) > max_distance)
		s->y = s->x;
	return (true);
}

bool				cylinder_collision(t_ray ray, t_cylinder *c, t_rpoint *p)
{
	bool			bcol;
	t_rpoint		bcollision;
	t_rpoint		eq_factors;
	t_dpoint		solutions;

	bcol = base_collision(ray, c, &bcollision);
	eq_factors = get_cyc_eq_factors(ray, c);
	if (find_collisions(eq_factors, &solutions) == false || \
		between_bases(ray, c, &solutions) == false)
	{
		if (bcol == false)
			return (false);
		*p = bcollision;
		return (true);
	}
	*p = closer(ray.p, new_point(ray.p, ray.vector, solutions.x), \
	new_point(ray.p, ray.vector, solutions.y));
	if (bcol == true)
		*p = closer(ray.p, *p, bcollision);
	return (true);
}
