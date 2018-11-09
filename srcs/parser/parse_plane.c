/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:45:18 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/09 18:07:11 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

static	bool	get_pos(t_obj *o, t_json_value *val)
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

static	bool	geet_vector(t_obj *o, t_json_value *val)
{
	int				*a;
	t_json_array	*arr;
	t_plane			*pl;

	pl = (t_plane *)o->obj;
	if (val == NULL)
		return (false);
	if (val->type == 3)
	{
		arr = (t_json_array *)val->ptr;
		a = (int *)arr->value[0]->ptr;
		pl->vector.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		pl->vector.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		pl->vector.z = (double)*a;
	}
	return (true);
}

bool	get_plane_inf(t_json_object *obj)
{
	t_obj		*o;

	o = malloc_object(2);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_pos(o, obj->pair[1]->value) == false)
			return (false);
	}
	else
		return (false);
	if (cmp_chars(obj->pair[2]->key->str, "vector", 0) == true)
	{
		if (geet_vector(o, obj->pair[2]->value) == false)
			return (false);
	}
	else
			return (false);
	if (cmp_chars(obj->pair[3]->key->str, "color", 0) == true)
		o->color = get_obj_color(obj->pair[3]->value);
	else
		return	(false);
	if (cmp_chars(obj->pair[4]->key->str, "rotate", 0) == true)
	{
		if (prerotate(o, obj->pair[4]->value, 2) == false)
			return (false);
	}
	put_inf_to_glob(o);
	return (true);
}
