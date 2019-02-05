/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pyra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:14:35 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:49:56 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

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
	else
		return (false);
	return (true);
}

static	bool	get_height(t_json_value *val, double *height)
{
	int		*a;

	a = 0;
	if (val == NULL)
		return (false);
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		*height = (double)*a;
	}
	else
		return (false);
	return (true);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o, double *height)
{
	if (i == 1)
		return (get_inf(o, val));
	if (i == 2)
		return (set_size(o, val));
	if (i == 3)
		return (get_height(val, height));
	if (i == 4)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	if (i == 5)
		return (true);
	if (i == 6)
		return (geet_reflex(val, o));
	return (false);
}

static	int		check_keys(char *str)
{
	if (cmp_chars(str, "pos", 0) == true)
		return (1);
	if (cmp_chars(str, "base_size", 0) == true)
		return (2);
	if (cmp_chars(str, "height", 0) == true)
		return (3);
	if (cmp_chars(str, "color", 0) == true)
		return (4);
	if (cmp_chars(str, "rotate", 0) == true)
		return (5);
	if (cmp_chars(str, "reflex", 0) == true)
		return (6);
	return (-1);
}

bool			get_pyra_inf(t_json_object *obj)
{
	t_obj			*o;
	int				i;
	double			height;

	i = 0;
	o = malloc_object(68);
	while (i++ < 6)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
			obj->pair[i]->value, o, &height) == false)
			return (false);
		if (i == 5 && check_keys(obj->pair[i]->key->str) == 5)
		{
			get_pyramid(o, o->size, height);
			if (prerotate(o, obj->pair[i]->value, 69) == false)
				return (false);
		}
	}
	put_inf_to_glob(o);
	return (true);
}
