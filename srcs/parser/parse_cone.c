/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:40:23 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:47:56 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

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
		if (!check_arr(arr) || arr->nb != 3)
			return (false);
		a = (int *)arr->value[0]->ptr;
		c->vector.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		c->vector.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		c->vector.z = (double)*a;
	}
	else
		return (false);
	return (true);
}

static	bool	cone_angle(t_obj *o, t_json_value *val)
{
	int		*a;
	t_cone	*c;

	c = (t_cone *)o->obj;
	a = 0;
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		c->angle = ((double)*a / 360) * (2 * PI);
	}
	else
		return (false);
	return (true);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o)
{
	static	t_checkcone	checkcon[4] = {{&get_inf, 1},
	{&geet_vector, 2}, {&cone_angle, 3}, {&verif_infinite, 4}};

	if (i > 0 && checkcon[i - 1].i == i)
		return (checkcon[i - 1].f(o, val));
	if (i == 5)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	if (i == 6)
		return (prerotate(o, val, 3));
	if (i == 7)
		return (geet_reflex(val, o));
	return (false);
}

static	int		check_keys(char *str)
{
	if (cmp_chars(str, "pos", 0) == true)
		return (1);
	if (cmp_chars(str, "vector", 0) == true)
		return (2);
	if (cmp_chars(str, "angle", 0) == true)
		return (3);
	if (cmp_chars(str, "INF", 0) == true)
		return (4);
	if (cmp_chars(str, "color", 0) == true)
		return (5);
	if (cmp_chars(str, "rotate", 0) == true)
		return (6);
	if (cmp_chars(str, "reflex", 0) == true)
		return (7);
	return (-1);
}

bool			get_cone_inf(t_json_object *obj)
{
	t_obj		*o;
	int			i;

	i = 0;
	o = malloc_object(3);
	while (i++ < 7)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
		obj->pair[i]->value, o) == false)
			return (false);
	}
	put_inf_to_glob(o);
	return (true);
}
