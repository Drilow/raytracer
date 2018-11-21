/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:37:43 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/21 14:01:33 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

static	bool	get_inf(t_obj *o,t_json_value *val)
{
	int				*a;
	t_json_array	*arr;
	t_sphere		*sph;

	sph = (t_sphere *)o->obj;
	if (val == NULL)
		return (false);
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		sph->radius = (double)*a; 
	}
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

bool	get_sphere_inf(t_json_object *obj)
{
	t_obj		*o;

	o = malloc_object(1);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_inf(o, obj->pair[1]->value) == false)
			return (false);
	}
	else
		return (false);
	if (cmp_chars(obj->pair[2]->key->str, "radius", 0) == true)
	{
		if (get_inf(o, obj->pair[2]->value) == false)
			return (false);
	}
	else
		return (false);
	if (cmp_chars(obj->pair[3]->key->str, "color", 0) == true)
		o->color = get_obj_color(obj->pair[3]->value);
	else
		return (false);
	put_inf_to_glob(o);
	return (true);
}
