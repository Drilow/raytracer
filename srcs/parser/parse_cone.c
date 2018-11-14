/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:40:23 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/14 14:46:18 by mabessir         ###   ########.fr       */
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
	t_cone			*c;

	c = (t_cone *)o->obj;
	if (val == NULL)
		return (false);
	if (val->type == 3)
	{
		arr = (t_json_array *)val->ptr;
		a = (int *)arr->value[0]->ptr;
		c->vector.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		c->vector.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		c->vector.z = (double)*a;
	}
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		c->angle = ((double)*a / 360) * (2 * PI);
	}
	return (true);
}

static	void	verif_inf(t_obj *o, t_json_value *val)
{
	bool	a;
	t_cone	*c;

	c = (t_cone *)o->obj;
	a = (bool)val->ptr;
	c->infinite = a;
}

bool	get_cone_inf(t_json_object *obj)
{
	t_obj		*o;

	o = malloc_object(3);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_pos(o, obj->pair[1]->value) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[2]->key->str, "vector", 0) == true)
	{
		if (geet_vector(o, obj->pair[2]->value) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[3]->key->str, "angle", 0) == true)
	{
		if (geet_vector(o, obj->pair[3]->value) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[4]->key->str, "INF", 0) == true)
		verif_inf(o, obj->pair[4]->value);
	if (cmp_chars(obj->pair[5]->key->str, "color", 0) == true)
		o->color = get_obj_color(obj->pair[5]->value);
	if (cmp_chars(obj->pair[6]->key->str, "rotate", 0) == true
	&& obj->pair[6]->value->type == 3)
	{
		if (prerotate(o, obj->pair[6]->value, 3) == false)
			return (false);
	}
	put_inf_to_glob(o);
	return (true);
}