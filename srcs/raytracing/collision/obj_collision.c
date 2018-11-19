/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:30:52 by alacrois          #+#    #+#             */
/*   Updated: 2018/10/24 17:10:08 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry/geometry.h>
#include <objects/object.h>
#include <maths/transformations.h>
#include <raytracing/collision.h>

#include <stdbool.h>

#include <libft.h>

static t_rpoint	add_rpoints(t_rpoint a, t_rpoint b)
{
	return (set_rpoint(a.x + b.x, a.y + b.y, a.z + b.z));
}


static bool		face_collision(t_ray ray, t_rpoint pos, t_vertex *face, t_collision *col, bool test)
{
	t_rpoint	tmp;
	double		a;
//	double		atmp;
	t_vertex	*tmpv;

//	if (test == true)
//		printf("debug1\n");
	if (plane_collision(ray, &(face->pl), set_rpoint(pos.x + face->p.x, pos.y + face->p.y, pos.z + face->p.z), &tmp) == false)
		return (false);
//	if (test == true)
//		printf("debug2\n");
	tmpv = face;
	a = 0;
	while (tmpv->next != NULL)
	{
		a = a + vangle(get_vector(tmp, add_rpoints(pos, tmpv->p)), get_vector(tmp, add_rpoints(pos, tmpv->next->p)));
		tmpv = tmpv->next;
	}
//	atmp = a;
//	if (test == true)
//		printf("a = %f\n", a);
	a = a + vangle(get_vector(tmp, add_rpoints(pos, tmpv->p)), get_vector(tmp, add_rpoints(pos, face->p)));
//	if (a < (2 * PI) * 0.999999 || a > (2 * PI) * 1.000001)
	if (a < (2 * PI * 0.9999999999) || isnan(a) != 0)
		return (false);
//	if (test == true)
//       printf("debug3\n");
	col->normal = face->pl.vector;
	col->p = tmp;
//	if (test == true)
//		printf("face_collision == true, a = %f, atmp = %f\n", a, atmp);
	if (test == true)
		return (true);
	return (true);
}


bool			poly_obj_collision(t_ray ray, t_poly_obj *po, t_collision *col, bool test)
{
	t_collision	fcol;
	t_collision	tmp;
	double		d;
	t_poly_obj	*potmp;

	d = -1;
	potmp = po;
	tmp.o = col->o;
	if (point_to_line_distance(col->o->position, ray.p, ray.vector) > po->max_d)
		return (false);
	while (potmp != NULL)
	{
		if (face_collision(ray, col->o->position, potmp->vertices, &tmp, test) == true && (d == -1 || deltasq(ray.p, tmp.p) < d))
		{
//			fcol = tmp;
			fcol.o = tmp.o;
			fcol.p = tmp.p;
			fcol.normal = tmp.normal;
			d = deltasq(ray.p, tmp.p);
		}
		potmp = potmp->next;
	}

	if (d == -1)
	{
//		ft_putendl("false");
		return (false);
	}
//	*col = fcol;
	col->p = fcol.p;
	col->normal = fcol.normal;
//	ft_putendl("true");
	return (true);
}

 /*
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
*/
