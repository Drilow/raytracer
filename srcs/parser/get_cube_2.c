#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

static t_rpoint         set_face_vector(t_vertex *face)
{
    face->pl.vector = cross_product(get_vector(face->p, face->next->p), \
                    get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, \
                get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, \
                                    -face->pl.vector.y, -face->pl.vector.z);
}

static t_vertex         *malloc_4v(void)
{
    t_vertex *face;

    face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	face->next->next->next = pmalloc_vertex();
    return (face);
}

static	t_vertex		*add_cube_face(t_rpoint f)
{
	t_vertex *face;

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
	face->pl.vector = set_face_vector(face);
    return (face);
}

static void             get_cube_2(t_poly_obj *o, double size, double maxd)
{
    o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, -size, 0));
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(size, 0, 0));
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(-size, 0, 0));
}

bool					get_cube(t_obj *c, double size)
{
	t_poly_obj	*o;
	double		maxd;

	size = size / 2;
	c->size = size;
	maxd = sqrt(3 * size * size);
	c->obj = pmalloc_po();
	o = c->obj;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, 0, size));
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, 0, -size));
	o->next = pmalloc_po();
	o = o->next;
	o->max_d = maxd;
	o->vertices = add_cube_face(set_rpoint(0, size, 0));
	get_cube_2(o, size, maxd);
	return (true);
}