/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:45:18 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/07 16:35:15 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

static	bool	get_pos(t_obj *o, t_json_value *val, int i)
{
	int				*a;
	t_json_array	*arr;

	if (val == NULL)
		return (false);
	o->type = 2;
	if (val->type == array && i == 0)
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

static	bool	geet_vector(t_obj *o, t_json_value *val, t_plane *pl, int i)
{
	int				*a;
	t_json_array	*arr;

	if (val == NULL)
		return (false);
	o->type = 2;
	if (val->type == array && i == 1)
	{
		arr = (t_json_array *)val->ptr;
		a = (int *)arr->value[0]->ptr;
		pl->vector.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		pl->vector.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		pl->vector.z = (double)*a;
		o->obj = (void *)pl;
	}
	return (true);
}

bool	get_plane_inf(t_json_object *obj, unsigned long nb)
{
	t_obj		o;
	t_plane		pl;

	if (obj->pair[nb]->value->type != array)
		return (false);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_pos(&o, obj->pair[1]->value, 0) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[2]->key->str, "vector", 0) == true)
	{
		if (geet_vector(&o, obj->pair[2]->value, &pl, 1) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[3]->key->str, "color", 0) == true)
		o.color = get_obj_color(obj->pair[3]->value);
	put_inf_to_glob(&o);
	return (true);
}
