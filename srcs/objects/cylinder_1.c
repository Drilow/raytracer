/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collision_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:33:05 by alacrois          #+#    #+#             */
/*   Updated: 2018/08/26 18:23:54 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <global.h>

static bool			bc_init(t_cylinder *c, t_plane *pl1, t_plane *pl2)
{
	if (c->infinite == true)
		return (false);
	pl1->vector = c->vector;
	pl2->vector = c->vector;
	return (true);
}

static bool			base_collision(t_ray ray, t_cylinder *c, \
									t_rpoint pos, t_rpoint *bc)
{
	t_rpoint		bcol1;
	t_rpoint		bcol2;
	t_plane			pl1;
	t_plane			pl2;
	t_rpoint		pl2_pos;

	if (bc_init(c, &pl1, &pl2) == false)
		return (false);
	pl2_pos = set_rpoint(pos.x + c->vector.x, \
						pos.y + c->vector.y, pos.z + c->vector.z);
	if (plane_collision(ray, &pl1, pos, &bcol1) == false \
		|| deltasq(pos, bcol1) > pow(c->radius, 2))
	{
		if (plane_collision(ray, &pl2, pl2_pos, &bcol2) == false \
			|| deltasq(pl2_pos, bcol2) > pow(c->radius, 2))
			return (false);
		*bc = bcol2;
		return (true);
	}
	else if (plane_collision(ray, &pl2, pl2_pos, &bcol2) == false \
		|| deltasq(pl2_pos, bcol2) > pow(c->radius, 2))
		*bc = bcol1;
	else
		*bc = closer(ray.p, bcol1, bcol2);
	return (true);
}

static bool			between_bases(t_ray ray, t_cylinder *c, \
								t_rpoint pos, t_dpoint *s)
{
	t_rpoint		p1;
	t_rpoint		p2;
	t_rpoint		ccenter;
	double			max_distance;

	if (c->infinite == true)
		return (true);
	p1 = new_point(ray.p, ray.vector, s->x);
	p2 = new_point(ray.p, ray.vector, s->y);
	ccenter.x = pos.x + (c->vector.x / 2);
	ccenter.y = pos.y + (c->vector.y / 2);
	ccenter.z = pos.z + (c->vector.z / 2);
	max_distance = pow(c->radius, 2) + deltasq(pos, ccenter);
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

bool				cylinder_collision(t_ray ray, t_obj *c, t_rpoint *p)
{
	bool			bcol;
	t_rpoint		bcollision;
	t_rpoint		eq_factors;
	t_dpoint		solutions;

	bcol = base_collision(ray, (t_cylinder *)c->obj, c->position, &bcollision);
	eq_factors = get_cyc_eq_factors(ray, (t_cylinder *)c->obj, c->position);
	if (find_collisions(eq_factors, &solutions, MIN_DISTANCE) == false || \
	between_bases(ray, (t_cylinder *)c->obj, c->position, &solutions) == false)
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
