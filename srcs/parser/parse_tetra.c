/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tetra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:44:02 by mabessir          #+#    #+#             */
/*   Updated: 2019/01/04 21:34:22 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <geometry/geometry.h>
#include <fcntl.h>

static	bool	get_tetra_size(t_obj *o, t_json_value *val)
{
	int		*a;

	if (val == NULL)
		return (false);
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		o->size = (double)*a;
	}
	else
		return (false);
	return (true);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o)
{
	if (i == 1)
		return (get_inf(o, val));
	if (i == 2)
		return (get_tetra_size(o, val));
	if (i == 3)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	if (i == 4)
		return (true);
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
	if (cmp_chars(str, "rotate", 0) == true)
		return (4);
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
	while (i++ < 4)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
			obj->pair[i]->value, o) == false)
			return (false);
		if (i == 4 && check_keys(obj->pair[i]->key->str) == 4)
		{
			get_tetrad(o, o->size);
			if (prerotate(o, obj->pair[i]->value, 67) == false)
				return (false);
		}
	}
	o->reflex = 0;
	put_inf_to_glob(o);
	return (true);
}
