/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:13:15 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/02 15:36:32 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>


static	int		get_obj_type(t_json_pair *pair)
{
	t_json_string	*string;
	char			*str;

	if (pair->value->type != string)
		return (0);
	string = (t_json_string *)pair->value->ptr;
	str = (char *)string->str;
	if (cmp_chars(str, "sphere", 0) == true)
		return (1);
	if (cmp_chars(str, "plane", 0) == true)
		return (2);
	if (cmp_chars(str, "cone", 0) == true)
		return (3);
	if (cmp_chars(str, "cylinder", 0) == true)
		return (4);
	if (cmp_chars(str, "obj", 0) == true)
		return (5);
	return (-1);
}

static 	bool	get_sphere_inf(t_json_object *obj, unsigned long nb)
{
	t_obj		o;
	t_sphere	*sph;
	bool		groboul;

	if (obj->pair[nb]->value->type != array)
		return (false);
	if (cmp_chars(obj->pair[1]->key->str, "pos", 0) == true)
	{
		if (get_inf(&o, 3) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[2]->key->str, "vector", 0) == true)
	{
		if (get_inf(&o, 3) == false)
			return (false);
	}
	if (cmp_chars(obj->pair[3]->key->str, "angle", 0) == true)
	if ((cmp_chars(obj->pair[4]->key->str, "INF", 0) == true)
	&& obj->pair[4]->value->type == bool)
		groboul = (bool)obj->pair[4]->value->ptr;
	if (cmp_chars(obj->pair[5]->key->str, "color", 0) == true)
		o.color = get_obj_color(obj->pair[5]->value);
	return (true);
}

static	bool	add_new_obj(t_json_array *list, unsigned long num)
{
	t_json_object	*obj;
	int				i;
	unsigned long	*nb;

	nb = 0;
	if (list->value[num]->type != object)
		return (false);
	obj = (t_json_object *)list->value[num]->ptr;
	if (cmp_chars(obj->pair[0]->key->str, "type", 0) == false)
		return (false);
	i = get_obj_type(obj->pair[0]);
	if (i == 1)
		get_sphere_inf(obj, num)
	return (true);
}

bool	parse_object(t_json_object *obj, unsigned long nb, int type)
{
	t_json_array	list;
	unsigned long	num;

	num = 0;
	if (obj->pair[nb]->value->type == array)
		return (false);
	list = (t_json_array *)obj->pair[nb]->value->ptr;
	while (num++ < list->nb)
		add_new_obj(list, num)
	if () 
	return (true);
}