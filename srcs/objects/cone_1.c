/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 19:57:41 by adleau            #+#    #+#             */
/*   Updated: 2018/11/23 12:29:48 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <objects/object.h>
#include <geometry/geometry.h>
#include <libft.h>
#include <global.h>

static bool	base_collision(t_ray ray, t_obj *c, t_rpoint *p)
{
	t_rpoint	bcenter;
	double		bradius;
	t_plane		pl;
	t_rpoint	pcol;
	t_rpoint	c_vector;

	c_vector = ((t_cone *)c->obj)->vector;
	bcenter.x = c->position.x + c_vector.x;
	bcenter.y = c->position.y + c_vector.y;
	bcenter.z = c->position.z + c_vector.z;
	bradius = vlength(c_vector) * tan(((t_cone *)c->obj)->angle);
	pl.vector = c_vector;
//	pl.p = bcenter;
	if (plane_collision(ray, &pl, bcenter, &pcol) == false)
		return (false);
	if (deltasq(bcenter, pcol) > (bradius * bradius))
		return (false);
	*p = pcol;
	return (true);
}

static bool	check_solutions(t_ray ray, t_obj *c, t_dpoint *solutions)
{
	t_rpoint	tmp1;
	t_rpoint	tmp2;
	double		max;
	double		c_angle;
	t_rpoint	c_vector;

	c_angle = ((t_cone *)c->obj)->angle;
	c_vector = ((t_cone *)c->obj)->vector;
	max = vlength(c_vector) / cos(c_angle);
	if (((t_cone *)c->obj)->infinite == true)
		return (true);
	tmp1 = get_vector(c->position, new_point(ray.p, ray.vector, solutions->x));
	tmp2 = get_vector(c->position, new_point(ray.p, ray.vector, solutions->y));
	if (vangle(c_vector, tmp1) >= (PI / 2) || vlength(tmp1) > max)
	{
		if (vangle(c_vector, tmp2) >= (PI / 2) || vlength(tmp2) > max)
			return (false);
		solutions->x = solutions->y;
	}
	else
	{
		if (vangle(c_vector, tmp2) >= (PI / 2) || vlength(tmp2) > max)
			solutions->y = solutions->x;
	}
	return (true);
}

#include <stdio.h>

bool			cone_collision(t_ray ray, t_obj *c, t_rpoint *p)
{
	t_rpoint	bcollision;
	t_rpoint	eq_factors;
	t_dpoint	solutions;

//	printf("object ptr %p id %d\n", c, c->type, ((t_cone*)c->obj));
	if (get_cc_eq_factors(ray, c, &eq_factors) == false)
		return (false);
	if (find_collisions(eq_factors, &solutions, MIN_DISTANCE) == false)
		return (false);
	if (check_solutions(ray, c, &solutions) == false)
		return (false);
	*p = closer(ray.p, new_point(ray.p, ray.vector, solutions.x), \
	new_point(ray.p, ray.vector, solutions.y));
	if (((t_cone *)c->obj)->infinite == false && base_collision(ray, c, &bcollision) == true)
		*p = closer(ray.p, *p, bcollision);
//	ft_putendl("true");
	return (true);
}
