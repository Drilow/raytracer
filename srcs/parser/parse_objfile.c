/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:03:39 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/15 18:39:58 by mabessir         ###   ########.fr       */
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
		a = (int *)arr->value[0]->ptr;
		o->position.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		o->position.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		o->position.z = (double)*a;
	}
	return (true);
}

bool	get_poly_objinf(t_json_object *obj)
{
	t_obj		*o;
	t_json_string *str;

	str = 0;
	o = malloc_object(6);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_inf(o, obj->pair[1]->value) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[2]->key->str, "adresse", 0) == true)
	{
		if (obj->pair[2]->value->type == 7)
			str = (t_json_string *)obj->pair[2]->value->ptr;
	}
	if (cmp_chars(obj->pair[3]->key->str, "color", 0) == true)
		o->color = get_obj_color(obj->pair[3]->value);
	o->obj = parse_obj(str->str);
	put_inf_to_glob(o);
	return (true);
}