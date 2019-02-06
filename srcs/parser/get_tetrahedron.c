/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetrahedron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:02:34 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:46:04 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

static void			set_face_vector(t_vertex *face)
{
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), \
						get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, \
				get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, \
							-face->pl.vector.y, -face->pl.vector.z);
}

static	t_vertex	*add_t_face_1(int fnb, double size)
{
	t_vertex		*face;
	double			height;
	double			h;

	face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	height = sqrt((size * size) - (pow(size / 2, 2)));
	h = height / 3;
	if (fnb == 1)
	{
		face->p = set_rpoint(0, -h, 2 * h);
		face->next->p = set_rpoint(size / 2, -h, -h);
		face->next->next->p = set_rpoint(-size / 2, -h, -h);
	}
	else if (fnb == 2)
	{
		face->p = set_rpoint(0, -h, 2 * h);
		face->next->p = set_rpoint(size / 2, -h, -h);
		face->next->next->p = set_rpoint(0, 2 * h, 0);
	}
	set_face_vector(face);
	return (face);
}

static	t_vertex	*add_t_face_2(int fnb, double size)
{
	t_vertex		*face;
	double			height;
	double			h;

	face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	height = sqrt((size * size) - (pow(size / 2, 2)));
	h = height / 3;
	if (fnb == 3)
	{
		face->p = set_rpoint(0, -h, 2 * h);
		face->next->p = set_rpoint(0, 2 * h, 0);
		face->next->next->p = set_rpoint(-size / 2, -h, -h);
	}
	else if (fnb == 4)
	{
		face->p = set_rpoint(0, 2 * h, 0);
		face->next->p = set_rpoint(size / 2, -h, -h);
		face->next->next->p = set_rpoint(-size / 2, -h, -h);
	}
	set_face_vector(face);
	return (face);
}

bool				get_tetrad(t_obj *t, double size)
{
	t_poly_obj		*o;

	t->size = size;
	t->obj = pmalloc_po();
	o = t->obj;
	o->max_d = size;
	o->vertices = add_t_face_1(1, size);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_t_face_1(2, size);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_t_face_2(3, size);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_t_face_2(4, size);
	return (true);
}

bool				set_tetrahedron(t_rpoint position, double size, t_obj *t)
{
	t_poly_obj *o;

	t->position = position;
	t->obj = pmalloc_po();
	o = t->obj;
	o->max_d = size;
	o->vertices = add_t_face_1(1, size);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_t_face_1(2, size);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_t_face_2(3, size);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_t_face_2(4, size);
	t->size = size;
	return (true);
}
