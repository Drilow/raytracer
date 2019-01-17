#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

// static	t_poly_obj		*malloc_po(void)
// {
// 	t_poly_obj *obj;

// 	if (!(obj = (t_poly_obj *)malloc(sizeof(t_poly_obj))))
//         exit_properly(1);
// 	obj->next = NULL;
// 	return (obj);
// }

// static	t_vertex		*malloc_vertex(void)
// {
// 	t_vertex *v;

// 	if (!(v = (t_vertex *)malloc(sizeof(t_vertex))))
//         exit_properly(1);
// 	v->next = NULL;
// 	return (v);
// }

static  t_vertex        *add_dode_face(t_rpoint **f, int i)
{
	t_vertex			*face;

	face = malloc_vertex();
	face->next = malloc_vertex();
	face->next->next = malloc_vertex();
	face->next->next->next = malloc_vertex();
	face->next->next->next->next = malloc_vertex();
	face->p = set_rpoint(f[i][0].x, f[i][0].y, f[i][0].z);
	face->next->p = set_rpoint(f[i][1].x, f[i][1].y, f[i][1].z);
	face->next->next->p = set_rpoint(f[i][2].x, f[i][2].y, f[i][2].z);
	face->next->next->next->p = set_rpoint(f[i][3].x, f[i][3].y, f[i][3].z);
	face->next->next->next->next->p = \
        set_rpoint(f[i][4].x, f[i][4].y, f[i][4].z);
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), \
                                    get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, \
                get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, \
                                    -face->pl.vector.y, -face->pl.vector.z);
	return (face);
}

static void             init_get_dode(t_rpoint **v, t_rpoint ***faces, \
                                        t_obj *d, double size)
{
    int                 i;

    i = -1;
	while (++i < 12)
    {
		if (!(*faces[i] = (t_rpoint *)malloc(sizeof(t_rpoint) * 5)))
            exit_properly(1);
    }
    get_dodecahedron_vertices(*v, size);
	get_dodecahedron_faces(*v, *faces);
    d->obj = malloc_po();
    ((t_poly_obj *)d->obj)->max_d = 4 * size;
}

bool					get_dodecahedron(t_obj *d, double size)
{
	t_poly_obj			*o;
	int					i;
	t_rpoint			v[21];
	t_rpoint			*faces[12];

    init_get_dode(&v, &faces, d, size);
    o = d->obj;
	i = -1;
	while (++i < 12)
	{
		o->vertices = add_dode_face((t_rpoint **)faces, i);
		if (i < 11)
		{
			o->next = malloc_po();
			o = o->next;
		}
	}
	i = -1;
	while (++i < 12)
		free(faces[i]);
	return (true);
}
