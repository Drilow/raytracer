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

static  t_vertex        *add_p_face_1(int fnb, double bsize, double h)
{
	t_vertex			*face;

	face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	if (fnb == 1)
	{
		face->p = set_rpoint(bsize / 2, 0, bsize / 2);
		face->next->p = set_rpoint(bsize / 2, 0, -bsize / 2);
		face->next->next->p = set_rpoint(-bsize / 2, 0, -bsize / 2);
		face->next->next->next = pmalloc_vertex();
		face->next->next->next->p = set_rpoint(-bsize / 2, 0, bsize / 2);
	}
	else if (fnb == 2)
	{
		face->p = set_rpoint(bsize / 2, 0, bsize / 2);
		face->next->p = set_rpoint(bsize / 2, 0, -bsize / 2);
		face->next->next->p = set_rpoint(0, h, 0);
	}
	face->pl.vector = set_face_vector(face);
	return (face);
}

static  t_vertex        *add_p_face_2(int fnb, double bsize, double h)
{
	t_vertex			*face;

	face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	if (fnb == 3)
	{
		face->p = set_rpoint(bsize / 2, 0, -bsize / 2);
        face->next->p =set_rpoint(-bsize / 2, 0, -bsize / 2);
        face->next->next->p = set_rpoint(0, h, 0);
	}
	else if (fnb == 4)
	{
		face->p = set_rpoint(-bsize / 2, 0, -bsize / 2);
        face->next->p =set_rpoint(-bsize / 2, 0, bsize / 2);
        face->next->next->p = set_rpoint(0, h, 0);
	}
	else if (fnb == 5)
    {
        face->p = set_rpoint(-bsize / 2, 0, bsize / 2);
        face->next->p =set_rpoint(bsize / 2, 0, bsize / 2);
        face->next->next->p = set_rpoint(0, h, 0);
    }
	face->pl.vector = set_face_vector(face);
	return (face);
}

bool					get_pyramid(t_obj *p, double base_size, double height)
{
	t_poly_obj			*o;

	p->obj = pmalloc_po();
	o = p->obj;
	o->max_d = base_size;
	if (height > base_size)
		o->max_d = height;
	o->vertices = add_p_face_1(1, base_size, height);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_p_face_1(2, base_size, height);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_p_face_2(3, base_size, height);
	o->next = pmalloc_po();
	o = o->next;
	o->vertices = add_p_face_2(4, base_size, height);
	o->next = pmalloc_po();
    o = o->next;
    o->vertices = add_p_face_2(5, base_size, height);
	return (true);
}