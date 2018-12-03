/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:31:57 by mabessir          #+#    #+#             */
/*   Updated: 2018/12/03 18:23:09 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

static	t_poly_obj		*malloc_po(void)
{
	t_poly_obj *obj;

	obj = (t_poly_obj *)malloc(sizeof(t_poly_obj));
	obj->next = NULL;
	return (obj);
}

static	t_vertex		*malloc_vertex(void)
{
	t_vertex *v;

	v = (t_vertex *)malloc(sizeof(t_vertex));
	v->next = NULL;
	return (v);
}

static	void			free_vlist(t_vertex **v_list)
{
	t_vertex *tmp;
	t_vertex *tmp_next;

	tmp = *v_list;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		free(tmp);
		tmp = tmp_next;
	}
}

static	bool			get_next_double(char *line, int *index, double *a)
{
	double	sign;
	double	tmp;
	int		digit_index;

	sign = 1;
	tmp = 0;
	while (line[*index] != '-' && ft_isdigit(line[*index]) == 0
		&& line[*index] != '\0')
		(*index)++;
	if (line[*index] == '-')
	{
		sign = -1;
		(*index)++;
	}
	if (line[*index] == '\0')
		return (false);
	if (ft_isdigit(line[*index]) == 0)
		return (get_next_double(line, index, a));
	while (ft_isdigit(line[*index]) == 1)
	{
		tmp = (tmp * 10) + (double)(line[*index] - '0');
		(*index)++;
	}
	if (line[*index] != '.')
	{
		*a = tmp * sign;
		return (true);
	}
	(*index)++;
	digit_index = 1;
	while (ft_isdigit(line[*index]) == 1)
	{
		tmp = tmp + ((double)(line[*index] - '0') / pow(10, digit_index));
		(*index)++;
		digit_index++;
	}
	*a = tmp * sign;
	return (true);
}

static	bool			parse_vertex(t_vertex *v, char *line, double size)
{
	int index;

	index = 0;
	if (get_next_double(line, &index, &(v->p.x)) == false)
		return (false);
	if (get_next_double(line, &index, &(v->p.y)) == false)
		return (false);
	if (get_next_double(line, &index, &(v->p.z)) == false)
		return (false);
	v->p.x = v->p.x * size;
	v->p.y = v->p.y * size;
	v->p.z = v->p.z * size;
	return (true);
}

static	bool			add_vertex(t_vertex **v_list, char *line, double size)
{
	t_vertex *tmp;
	t_vertex *new;

	new = malloc_vertex();
	if (parse_vertex(new, line, size) == false)
	{
		return (false);
	}
	if (*v_list == NULL)
		*v_list = new;
	else
	{
		tmp = *v_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (true);
}

static	bool			get_vertex(t_vertex *v_list, int position, t_vertex *v)
{
	t_vertex	*tmp;
	int			index;

	tmp = v_list;
	index = 0;
	while (tmp != NULL)
	{
		index++;
		if (position == index)
		{
			v->p = tmp->p;
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

static	bool			parse_face(t_poly_obj *face, char *line, t_vertex *v_list)
{
	int			line_index;
	double		v_index;
	t_vertex	*vertices;
	int			v_nb;

	v_index = 0;
	line_index = 0;
	vertices = NULL;
	v_nb = 0;
	while (get_next_double(line, &line_index, &v_index) == true)
	{
		v_nb++;
		if (vertices == NULL)
		{
			vertices = malloc_vertex();
			face->vertices = vertices;
			if (get_vertex(v_list, (int)v_index, vertices) == false)
				return (false);
		}
		else
		{
			while (vertices->next != NULL)
				vertices = vertices->next;
			vertices->next = malloc_vertex();
			if (get_vertex(v_list, (int)v_index, vertices->next) == false)
				return (false);
		}
	}
	if (v_nb < 3)
		return (false);
	return (true);
}

static	bool			add_face(t_poly_obj **obj, t_vertex *v_list, char *line)
{
	t_poly_obj *tmp;
	t_poly_obj *new;

	new = malloc_po();
	if (parse_face(new, line, v_list) == false)
		return (false);
	if (*obj == NULL)
		*obj = new;
	else
	{
		tmp = *obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (true);
}

static	bool			read_line(t_poly_obj **obj, t_vertex **v_list, char *line, double size)
{
	if (line[0] == 'v')
		return (add_vertex(v_list, line, size));
	else if (line[0] == 'f' && *v_list != NULL)
		return (add_face(obj, *v_list, line));
//	return (false);
	return (true);
}

static	void			get_face_maxd(t_vertex *f, double *d)
{
	double tmp_d;
	double tmp;

	tmp_d = 0;
	while (f != NULL)
	{
		tmp = sqrt(deltasq(set_rpoint(0, 0, 0), f->p));
		if (tmp_d < tmp)
			tmp_d = tmp;
		f = f->next;
	}
	if (tmp_d > *d)
		*d = tmp_d;
}

void					set_obj(t_obj *o)
{
	t_poly_obj	*tmp;
	t_vertex	*face;
	t_rpoint	pos;
	double		tmp_d;

	tmp = (t_poly_obj *)o->obj;
	tmp_d = 0;
	while (tmp != NULL)
	{
		face = tmp->vertices;
		pos = o->position;
		get_face_maxd(face, &tmp_d);
		face->pl.vector = cross_product(get_vector(face->p, face->next->p), get_vector(face->p, face->next->next->p));
		tmp = tmp->next;
	}
	((t_poly_obj *)o->obj)->max_d = tmp_d;
}

t_poly_obj				*parse_obj(char *scene_line, double size)
{
	t_poly_obj	*obj;
	t_vertex	*v_list;
	int			fd;
	char		*line;
	int			i;

	obj = NULL;
	v_list = NULL;
	fd = open(scene_line, O_RDONLY);
	if (fd == -1)
		ft_exit("Couldn't open obj file", 1);
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (read_line(&obj, &v_list, line, size) == false)
		{
			free(line);
			if (v_list != NULL)
				free_vlist(&v_list);
			ft_putstr("Parsing ended at line ");
			ft_putnbr(i);
			ft_putstr("\n");
			return (obj);
		}
		i++;
		free(line);
	}
	free_vlist(&v_list);
	return (obj);
}

static	t_vertex		*add_cube_face(t_rpoint f)
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

bool					get_cube(t_obj *c, double size)
{
	t_poly_obj	*o;
	double		maxd;

	size = size / 2;
	c->size = size;
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
	return (true);
}

static	t_vertex		*add_t_face(int fnb, double size)
{
	t_vertex	*face;
	double		height;
	double		h;

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
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, -face->pl.vector.y, face->pl.vector.z);
	return (face);
}

bool					get_tetrad(t_obj *t, double size)
{
	t_poly_obj *o;

	t->size = size;
	t->obj = malloc_po();
	o = t->obj;
	o->max_d = size;
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
	return (true);
}

static  t_vertex        *add_p_face(int fnb, double bsize, double h)
{
	t_vertex			*face;

	face = malloc_vertex();
	face->next = malloc_vertex();
	face->next->next = malloc_vertex();
	if (fnb == 1)
	{
		face->p = set_rpoint(bsize / 2, 0, bsize / 2);
		face->next->p = set_rpoint(bsize / 2, 0, -bsize / 2);
		face->next->next->p = set_rpoint(-bsize / 2, 0, -bsize / 2);
		face->next->next->next = malloc_vertex();
		face->next->next->next->p = set_rpoint(-bsize / 2, 0, bsize / 2);
	}
	else if (fnb == 2)
	{
		face->p = set_rpoint(bsize / 2, 0, bsize / 2);
		face->next->p = set_rpoint(bsize / 2, 0, -bsize / 2);
		face->next->next->p = set_rpoint(0, h, 0);
	}
	else if (fnb == 3)
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
	face->pl.vector = cross_product(get_vector(face->p, face->next->p), get_vector(face->p, face->next->next->p));
	if (vangle(face->pl.vector, get_vector(face->p, set_rpoint(0, 0, 0))) < (PI / 2))
		face->pl.vector = set_rpoint(-face->pl.vector.x, -face->pl.vector.y, face->pl.vector.z);
// ATTENTION (au desssus) -face->pl.vector.z ??
	return (face);
}

bool					get_pyramid(t_obj *p, double base_size, double height)
{
	t_poly_obj			*o;

	p->obj = malloc_po();
	o = p->obj;
	o->max_d = base_size;
	if (height > base_size)
		o->max_d = height;
	o->vertices = add_p_face(1, base_size, height);
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_p_face(2, base_size, height);
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_p_face(3, base_size, height);
	o->next = malloc_po();
	o = o->next;
	o->vertices = add_p_face(4, base_size, height);
	o->next = malloc_po();
    o = o->next;
    o->vertices = add_p_face(5, base_size, height);
	return (true);
}
