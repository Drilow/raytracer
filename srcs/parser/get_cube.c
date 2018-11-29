/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:01:48 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/29 13:13:59 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

static	t_poly_obj	*malloc_po(void)
{
	t_poly_obj *obj;

	obj = (t_poly_obj *)malloc(sizeof(t_poly_obj));
	obj->next = NULL;
	return (obj);
}

static	t_vertex	*malloc_vertex(void)
{
	t_vertex *v;

	v = (t_vertex *)malloc(sizeof(t_vertex));
	v->next = NULL;
	return (v);
}

static	t_vertex	*add_cube_face(t_rpoint f)
{
	t_vertex *face;

	face = malloc_vertex();
	face->next = malloc_vertex();
	face->next->next = malloc_vertex();
	face->next->next->next = malloc_vertex();
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
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, -face->pl.vector.y, face->pl.vector.z);
	return (face);
}

bool				set_cube(t_rpoint position, double size, t_obj *c)
{
	t_poly_obj	*o;
	double		maxd;

	c->position = position;
	size = size / 2;
	maxd = sqrt(3 * size * size);
	c->obj = malloc_po();
	o = c->obj;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, 0, size));
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_cube_face(set_rpoint(0, 0, -size));
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_cube_face(set_rpoint(0, size, 0));
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_cube_face(set_rpoint(0, -size, 0));
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_cube_face(set_rpoint(size, 0, 0));
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_cube_face(set_rpoint(-size, 0, 0));
	c->size = size;
	return (true);
}
