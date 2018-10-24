#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

static t_poly_obj	*malloc_po(void)
{
  t_poly_obj		*obj;

  obj = (t_poly_obj *)malloc(sizeof(t_poly_obj));
  obj->next = NULL;
  return (obj);
}

static t_vertex		*malloc_vertex(void)
{
  t_vertex			*v;

  v = (t_vertex *)malloc(sizeof(t_vertex));
  v->next = NULL;
  return (v);
}

static t_vertex       *add_t_face(int fnb, double size)
{
	t_vertex		*face;
	double			height;
	double			h;

	face = malloc_vertex();
	face->next = malloc_vertex();
	face->next->next = malloc_vertex();
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
	else if (fnb == 3)
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

//	face->pl.p = set_rpoint(pos.x + face->p.x, pos.y + face->p.y, pos.z + face->p.z);
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, -face->pl.vector.y, face->pl.vector.z);
	return (face);
}

bool			set_tetrahedron(t_rpoint position, double size, t_obj *t)
{
	t_poly_obj	*o;
//	double		maxd;

	t->position = position;
// distance au centre :
//	size = size / 2;
//	maxd = sqrt(3 * size * size);
	t->obj = malloc_po();
	o = t->obj;
// a faire : calculer valeur exact de maxd
	o->max_d = size;
//	o->vertices = add_t_face(1, size, t->position);
	o->vertices = add_t_face(1, size);

	o->next = malloc_po();
	o = o->next;
	o->vertices = add_t_face(2, size);
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_t_face(3, size);
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_t_face(4, size);
	t->size = size;
    return (true);
}
