/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:45:18 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/30 18:58:24 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

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
		if (!check_arr(arr) && arr->nb != 3)
			return (false);
		a = (int *)arr->value[0]->ptr;
		pl->vector.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		pl->vector.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		pl->vector.z = (double)*a;
	}
	return (true);
}

static	bool	call_parse(int i, t_json_value *val, t_obj *o)
{
	static t_checkplane checkplane[2] = {{&get_inf, 1},
	{&geet_vector, 2}};

	if (i > 0 && checkplane[i - 1].i == i)
		return (checkplane[i - 1].f(o, val));
	if (i == 3)
	{
		o->color = get_obj_color(val);
		return (true);
	}
	if (i == 4)
		return (prerotate(o, val, 2));
	return (false);
}

static	int		check_keys(char *str)
{
	if (cmp_chars(str, "pos", 0) == true)
		return (1);
	if (cmp_chars(str, "vector", 0) == true)
		return (2);
	if (cmp_chars(str, "color", 0) == true)
		return (3);
	if (cmp_chars(str, "rotate", 0) == true)
		return (4);
	return (-1);
}

bool			get_plane_inf(t_json_object *obj)
{
	t_obj		*o;
	int			i;

	i = 0;
	o = malloc_object(2);
	while (i++ < 4)
	{
		if (call_parse(check_keys(obj->pair[i]->key->str),
		obj->pair[i]->value, o) == false)
			return (false);
	}
	put_inf_to_glob(o);
	return (true);
}
