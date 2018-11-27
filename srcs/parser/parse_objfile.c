/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:03:39 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/27 16:03:14 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <geometry/geometry.h>
#include <fcntl.h>

extern t_global g_global;

static	bool	get_inf(t_obj *o,t_json_value *val)
{
	int				*a;
	t_json_array	*arr;

	if (val == NULL)
		return (false);
	if (val->type == 3)
	{
		arr = (t_json_array *)val->ptr;
		if (!check_arr(arr) && arr->nb != 3)
			return (false);
		a = (int *)arr->value[0]->ptr;
		o->position.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		o->position.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		o->position.z = (double)*a;
	}
	return (true);
}
static	bool	set_size(t_obj *o, t_json_value *val)
{
	int		*a;

	a = 0;
	if (val == NULL)
		return (false);
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		o->size = (double)*a;
	}
	return (true);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o)
{
	if (i == 1)
	{
		if (get_inf(o, val))
			return (true);
		else
			return (false);
	}
	if (i == 2)
	{
		if (set_size(o, val))
			return (true);
		else
			return (false);
	}
	if (i == 3)
		return (true);
	if (i == 4)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	return (false);
}
static	int 	check_keys(char *str)
{
	if (cmp_chars(str, "pos", 0) == true)
		return (1);
	if (cmp_chars(str, "size", 0) == true)
		return (2);
	if (cmp_chars(str, "adresse", 0) == true)
		return (3);
	if (cmp_chars(str, "color", 0) == true)
		return (4);
	return (-1);
}
bool	get_poly_objinf(t_json_object *obj)
{
	t_obj			*o;
	t_json_string	*str;
	int				i;

	str = 0;
	i = 0;
	o = malloc_object(6);
	while (i++ < 4)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str), obj->pair[i]->value, o) == false)
			return (false);
		if (i == 3)
		{
			if (obj->pair[i]->value->type == 7)
				str = (t_json_string *)obj->pair[i]->value->ptr;
		}
	}
	get_poly_obj(str->str, o);
	put_inf_to_glob(o);
	return (true);
}