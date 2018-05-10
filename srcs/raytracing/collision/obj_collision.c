/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:30:52 by alacrois          #+#    #+#             */
/*   Updated: 2018/05/10 10:08:48 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry/geometry.h>
#include <objects/object.h>
#include <maths/transformations.h>
#include <raytracing/collision.h>

static t_rpoint	add_rpoints(t_rpoint a, t_rpoint b)
{
	return (set_rpoint(a.x + b.x, a.y + b.y, a.z + b.z));
}

static bool	face_collision(t_ray ray, t_rpoint pos, t_vertex *face, t_collision *col)
{
	t_rpoint	tmp;
	double		a;
	t_vertex	*tmpv;

	if (plane_collision(ray, &(face->pl), &tmp) == false)
		return (false);
	tmpv = face;
	a = 0;
	while (tmpv->next != NULL)
	{
		a = a + vangle(get_vector(tmp, add_rpoints(pos, tmpv->p)), get_vector(tmp, add_rpoints(pos, tmpv->next->p)));
		tmpv = tmpv->next;
	}
	a = a + vangle(get_vector(tmp, add_rpoints(pos, tmpv->p)), get_vector(tmp, add_rpoints(pos, face->p)));
	if (a < (2 * PI) * 0.999999 || a > (2 * PI) * 1.000001)
		return (false);
	col->normal = face->pl.vector;
	col->p = tmp;
	return (true);
}

bool			poly_obj_collision(t_ray ray, t_poly_obj *po, t_collision *col)
{
	t_collision	fcol;
	t_collision	tmp;
	double		d;
	t_poly_obj	*potmp;

	d = -1;
	potmp = po;
		if (point_to_line_distance(col->o->position, ray.p, ray.vector) > po->max_d)
		return (false);
	while (potmp != NULL)
	{
		if (face_collision(ray, col->o->position, potmp->vertices, &tmp) == true && (d == -1 || deltasq(ray.p, tmp.p) < d))
		{
			fcol = tmp;
			d = deltasq(ray.p, tmp.p);
		}
		potmp = potmp->next;
	}

	if (d == -1)
		return (false);
	*col = fcol;
	return (true);
}
