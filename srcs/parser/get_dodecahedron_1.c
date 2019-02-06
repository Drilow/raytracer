/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dodecahedron_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 10:29:50 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 16:24:33 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

static	t_vertex		*add_dode_face(t_rpoint **f, int i)
{
	t_vertex			*face;

	face = pmalloc_vertex();
	face->next = pmalloc_vertex();
	face->next->next = pmalloc_vertex();
	face->next->next->next = pmalloc_vertex();
	face->next->next->next->next = pmalloc_vertex();
	face->p = set_rpoint(f[i][0].x, f[i][0].y, f[i][0].z);
	face->next->p = set_rpoint(f[i][1].x, f[i][1].y, f[i][1].z);
	face->next->next->p = set_rpoint(f[i][2].x, f[i][2].y, f[i][2].z);
	face->next->next->next->p = set_rpoint(f[i][3].x, f[i][3].y, f[i][3].z);
	face->next->next->next->next->p = set_rpoint(f[i][4].x
	, f[i][4].y, f[i][4].z);
	face->pl.vector = cross_product(get_vector(face->p, face->next->p)
	, get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, get_vector(face->p,
	set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x,
		-face->pl.vector.y, -face->pl.vector.z);
	return (face);
}

static t_rpoint			**init_get_dode(t_rpoint *v, t_obj *d, double size)
{
	int					i;
	t_rpoint			**faces;

	if (!(faces = (t_rpoint **)malloc(sizeof(t_rpoint *) * 12)))
		ft_exit("Malloc error ('get_dodecahedron_1.c' --> Ln 49)", 1);
	i = -1;
	while (++i < 12)
	{
		if (!(faces[i] = (t_rpoint *)malloc(sizeof(t_rpoint) * 5)))
			ft_exit("Malloc error ('get_dodecahedron_1.c' --> Ln 54)", 1);
	}
	get_dodecahedron_vertices(v, size);
	get_dodecahedron_faces(v, faces);
	d->obj = pmalloc_po();
	((t_poly_obj *)d->obj)->max_d = 4 * size;
	return (faces);
}

bool					get_dodecahedron(t_obj *d, double size)
{
	t_poly_obj			*o;
	int					i;
	t_rpoint			v[21];
	t_rpoint			**faces;

	faces = init_get_dode(v, d, size);
	o = d->obj;
	i = -1;
	while (++i < 12)
	{
		o->vertices = add_dode_face((t_rpoint **)faces, i);
		if (i < 11)
		{
			o->next = pmalloc_po();
			o = o->next;
		}
	}
	i = -1;
	while (++i < 12)
		free(faces[i]);
	free(faces);
	d->size = size;
	return (true);
}
