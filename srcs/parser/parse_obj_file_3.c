/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:05:08 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/05 15:49:27 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

static bool			parse_vertex(t_vertex *v, char *line, double size)
{
	int				index;

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

bool				add_vertex(t_vertex **v_list, char *line, double size)
{
	t_vertex		*tmp;
	t_vertex		*new;

	new = pmalloc_vertex();
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

static bool			get_vertex(t_vertex *v_list, int position, t_vertex *v)
{
	t_vertex		*tmp;
	int				index;

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

static bool			parse_face_2(t_vertex *vertices, \
								t_vertex *v_list, double v_index)
{
	while (vertices->next != NULL)
		vertices = vertices->next;
	vertices->next = pmalloc_vertex();
	if (get_vertex(v_list, (int)v_index, vertices->next) == false)
		return (false);
	return (true);
}

bool				parse_face(t_poly_obj *face, char *line, t_vertex *v_list)
{
	int				line_index;
	double			v_index;
	t_vertex		*vertices;
	int				v_nb;

	v_index = 0;
	line_index = 0;
	vertices = NULL;
	v_nb = 0;
	while (get_next_double(line, &line_index, &v_index) == true)
	{
		v_nb++;
		if (vertices == NULL)
		{
			vertices = pmalloc_vertex();
			face->vertices = vertices;
			if (get_vertex(v_list, (int)v_index, vertices) == false)
				return (false);
		}
		else if (parse_face_2(vertices, v_list, v_index) == false)
			return (false);
	}
	if (v_nb < 3)
		return (false);
	return (true);
}
