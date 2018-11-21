/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tetra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:44:02 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/21 11:48:13 by mabessir         ###   ########.fr       */
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

static	double	get_tetra_size(t_json_value *val)
{
	int *a;
	double size;

	size = 0;
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		printf("%d\n", *a);
		size = (double)*a; 
		printf("%f\n", size);
	}
	return (size);
}

bool	get_tetra_inf(t_json_object *obj)
{
	t_obj		*o;
	double		size;

	o = malloc_object(67);
	size = 0;
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_inf(o, obj->pair[1]->value) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[2]->key->str, "size", 0) == true)
	{
		if (obj->pair[2]->value->type == 5)
			size = get_tetra_size(obj->pair[2]->value);
	}
	if (cmp_chars(obj->pair[3]->key->str, "color", 0) == true)
		o->color = get_obj_color(obj->pair[3]->value);
	get_tetrahedron(o, size);
	put_inf_to_glob(o);
	return (true);
}
