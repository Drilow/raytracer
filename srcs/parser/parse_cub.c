/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:03:39 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:48:05 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

static	bool	get_cub_size(t_obj *o, t_json_value *val)
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
		return (get_cub_size(o, val));
	if (i == 3)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	if (i == 4)
		return (true);
	if (i == 5)
		return (geet_reflex(val, o));
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
	if (cmp_chars(str, "reflex", 0) == true)
		return (5);
	return (-1);
}

bool			get_cube_inf(t_json_object *obj)
{
	t_obj		*o;
	double		size;
	int			i;

	i = 0;
	o = malloc_object(66);
	size = 1;
	while (i++ < 5)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
			obj->pair[i]->value, o) == false)
			return (false);
		if (i == 4 && check_keys(obj->pair[i]->key->str) == 4)
		{
			get_cube(o, o->size);
			if (prerotate(o, obj->pair[i]->value, 66) == false)
				return (false);
		}
	}
	put_inf_to_glob(o);
	return (true);
}
