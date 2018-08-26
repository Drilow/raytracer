/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 20:51:38 by alacrois          #+#    #+#             */
/*   Updated: 2018/08/19 17:53:19 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <extra/extra_defs.h>
#include <parser/parser.h>

#include <libft.h>

bool			cmp_chars(char *s, char *o, int start)
{
	int			is;
	int			io;

	is = start - 1;
	io = -1;
	while (o[++io] != '\0')
	{
		if (s[++is] != o[io])
			return (false);
	}
	return (true);
}


static bool		get_poly_obj(char *s, t_obj *o, int *i)
{
//	int			i;

	o->obj = parse_obj(s);
	*i = 4;
	while (s[*i] != ' ')
		(*i)++;
	if (o->obj == NULL)
		ft_putendl("((t_obj *)new)->obj == NULL\n");
	if (o->obj == NULL || get_next_rpoint(s, &(o->position), i) == false)
		return (false);
	set_obj(o);
	return (true);
}

static bool		get_obj_core_2(char *s, t_obj *obj, int *index)
{
  /*
	if (obj->type == 1 && \
		get_sphere(s, (t_sphere *)obj->obj, index) == false)
		return (false);
	if (obj->type == 2 && \
		get_plane(s, (t_plane *)obj->obj, index) == false)
		return (false);
	if (obj->type == 3 && \
		get_cone(s, (t_cone *)obj->obj, index) == false)
		return (false);
	if (obj->type == 4 && \
		get_cylinder(s, (t_cylinder *)obj->obj, index) == false)
		return (false);
	if (obj->type == 66 && \
		get_cube(s, obj, index) == false)
		return (false);
	if (obj->type == 67 && \
		get_tetrahedron(s, obj, index) == false)
		return (false);
  */
  if (obj->type == 1 && \
		get_sphere(s, obj, index) == false)
		return (false);
	if (obj->type == 2 && \
		get_plane(s, obj, index) == false)
		return (false);
	if (obj->type == 3 && \
		get_cone(s, obj, index) == false)
		return (false);
	if (obj->type == 4 && \
		get_cylinder(s, obj, index) == false)
		return (false);
	if (obj->type == 6 && \
		get_poly_obj(s, obj, index) == false)
		return (false);
	if (obj->type == 66 && \
		get_cube(s, obj, index) == false)
		return (false);
	if (obj->type == 67 && \
		get_tetrahedron(s, obj, index) == false)
		return (false);
	return (true);
}


bool			get_obj_core(char *s, t_obj *obj, int *index, t_rgb *clr)
{
	t_rgb		*color;

	
	if (obj == NULL)
		color = clr;
	else
		color = &(obj->color);
	if (obj != NULL && get_obj_core_2(s, obj, index) == false)
		return (false);
	if (get_next_nb(s, index, NULL, &(color->r)) == false || \
		get_next_nb(s, index, NULL, &(color->g)) == false || \
		get_next_nb(s, index, NULL, &(color->b)) == false || \
		get_next_nb(s, index, NULL, &(color->trans)) == false)
		return (false);
	return (true);
}
