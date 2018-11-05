/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:37:43 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/05 13:32:05 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

static	bool	get_inf(t_obj *o,t_json_value *val, t_sphere *sph int i)
{
	int				*a;
	t_json_array	*arr;

	if (val == NULL)
		return (false);
	o->type = 1;
	if (val->type == number || val->type == integer)
	{
		a = (double *)val->ptr;
		sph->radius = *a; 
		o->obj = (void *)sph;
	}
	if (val->type == array)
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

bool	get_sphere_inf(t_json_object *obj, unsigned long nb)
{
	t_obj		o;
	t_sphere	sph;

	if (obj->pair[nb]->value->type != array)
		return (false);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_inf(&o, obj->pair[1]->value, &sph, 3) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[2]->key->str, "radius", 0) == true)
	{
		if (get_inf(&o, obj->pair[2]->value, &sph, 1) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[5]->key->str, "color", 0) == true)
		o.color = get_obj_color(obj->pair[5]->value);
	return (true);
}
