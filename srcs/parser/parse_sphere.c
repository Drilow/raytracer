/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:37:43 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:50:02 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

static	bool	get_sph_radius(t_obj *o, t_json_value *val)
{
	int				*a;
	t_sphere		*sph;

	sph = (t_sphere *)o->obj;
	if (val == NULL)
		return (false);
	if (val->type == 5)
	{
		a = (int *)val->ptr;
		sph->radius = (double)*a;
	}
	else
		return (false);
	return (true);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o)
{
	if (i == 1)
		return (get_inf(o, val));
	if (i == 2)
		return (get_sph_radius(o, val));
	if (i == 3)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	if (i == 4)
		return (geet_reflex(val, o));
	return (false);
}

static	int		check_keys(char *str)
{
	if (cmp_chars(str, "pos", 0) == true)
		return (1);
	if (cmp_chars(str, "radius", 0) == true)
		return (2);
	if (cmp_chars(str, "color", 0) == true)
		return (3);
	if (cmp_chars(str, "reflex", 0) == true)
		return (4);
	return (-1);
}

bool			get_sphere_inf(t_json_object *obj)
{
	t_obj		*o;
	int			i;

	i = 0;
	o = malloc_object2(1);
	while (i++ < 4)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
		obj->pair[i]->value, o) == false)
			return (false);
	}
	put_inf_to_glob(o);
	return (true);
}
