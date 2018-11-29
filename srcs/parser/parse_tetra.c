/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tetra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:44:02 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/29 10:17:25 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <geometry/geometry.h>
#include <fcntl.h>

static	double	get_tetra_size(t_json_value *val)
{
	int		*a;
	double	size;

	size = 1;
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		size = (double)*a;
	}
	return (size);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o)
{
	if (i == 1)
		return (get_inf(o, val));
	if (i == 2)
		return (true);
	if (i == 3)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	return (false);
}

static	int		check_keys(char *str)
{
	if (cmp_chars(str, "pos", 0) == true)
		return (1);
	if (cmp_chars(str, "size", 0) == true)
		return (2);
	if (cmp_chars(str, "color", 0) == true)
		return (3);
	return (-1);
}

bool			get_tetra_inf(t_json_object *obj)
{
	t_obj		*o;
	double		size;
	int			i;

	i = 0;
	o = malloc_object(67);
	size = 1;
	while (i++ < 3)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
			obj->pair[i]->value, o) == false)
			return (false);
		if (i == 2)
		{
			if (obj->pair[2]->value->type == 5)
			{
				if ((size = get_tetra_size(obj->pair[2]->value)) <= 0)
					return (false);
			}
		}
	}
	get_tetrahedron(o, size);
	put_inf_to_glob(o);
	return (true);
}
