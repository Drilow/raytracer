/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:01:48 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:43:40 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

static void				set_face_vector(t_vertex *face)
{
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), \
						get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, \
				get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, \
							-face->pl.vector.y, -face->pl.vector.z);
}

static t_vertex			*malloc_4v(void)
{
	t_vertex			*face;

	face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	face->next->next->next = pmalloc_vertex();
	return (face);
}

static t_vertex			*add_cube_face(t_rpoint f)
{
	t_vertex			*face;

	face = malloc_4v();
	if (f.x != 0)
	{
		face->p = set_rpoint(f.x, -f.x, -f.x);
		face->next->p = set_rpoint(f.x, -f.x, f.x);
		face->next->next->p = set_rpoint(f.x, f.x, f.x);
		face->next->next->next->p = set_rpoint(f.x, f.x, -f.x);
	}
	else if (f.y != 0)
	{
		face->p = set_rpoint(-f.y, f.y, -f.y);
		face->next->p = set_rpoint(f.y, f.y, -f.y);
		face->next->next->p = set_rpoint(f.y, f.y, f.y);
		face->next->next->next->p = set_rpoint(-f.y, f.y, f.y);
	}
	else if (f.z != 0)
	{
		face->p = set_rpoint(-f.z, -f.z, f.z);
		face->next->p = set_rpoint(-f.z, f.z, f.z);
		face->next->next->p = set_rpoint(f.z, f.z, f.z);
		face->next->next->next->p = set_rpoint(f.z, -f.z, f.z);
	}
	return (face);
}

static void				get_cube_2(t_poly_obj *o, double size, double maxd)
{
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, -size, 0));
	set_face_vector(o->vertices);
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(size, 0, 0));
	set_face_vector(o->vertices);
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(-size, 0, 0));
	set_face_vector(o->vertices);
}

bool					set_cube(t_rpoint position, double size, t_obj *c)
{
	t_poly_obj			*o;
	double				maxd;

	c->position = position;
	size = size / 2;
	maxd = sqrt(3 * size * size);
	c->obj = pmalloc_po();
	o = c->obj;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, 0, size));
	set_face_vector(o->vertices);
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, 0, -size));
	set_face_vector(o->vertices);
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, size, 0));
	set_face_vector(o->vertices);
	get_cube_2(o, size, maxd);
	c->size = size;
	return (true);
}
