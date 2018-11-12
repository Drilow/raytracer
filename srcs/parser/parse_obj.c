/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:13:15 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/12 17:24:33 by mabessir         ###   ########.fr       */
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
/*
static	bool	get_inf(t_obj *o,t_json_value *val, int i)
{
	double	*a;
	t_json_array *arr;

	if (val == NULL)
		return (false);
	if (val->type == number || val->type == integer)
	{
		a = (double *)val->ptr;
		o->
	}
	return (true);
}
*/

bool			prerotate(t_obj *obj, t_json_value *val, int type)
{
	t_rpoint		*t;
	t_json_array	*arr;
	int				*a;

	if (!(t =(t_rpoint *)malloc(sizeof(t_point))))
		return (false);
	if (val == NULL || val->type != 3)
		return (false);
	arr = (t_json_array *)val->ptr;
	if (arr->nb == 3)
	{
		a = (int *)arr->value[0]->ptr;
		t->x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		t->y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		t->z = (double)*a;	
	}
	rotate_obj(obj, type, *t);
	return (true);
}
static	int		get_obj_type(t_json_pair *pair)
{
	t_json_string	*string;
	char			*str;

	if (pair->value->type != 7)
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
		return (6);
	return (-1);
}

static	bool	add_new_obj(t_json_array *list, unsigned long num)
{
	t_json_object	*obj;
	int				i;

	nb = 0;
	if (list->value[num] == NULL || list->value[num]->type != 4)
		return (false);
	obj = (t_json_object *)list->value[num]->ptr;
	if (obj->nb > 7)
		return (false);
	if (cmp_chars(obj->pair[0]->key->str, "type", 0) == false)
		return (false);
	if ((i = get_obj_type(obj->pair[0])) == -1)
		return (false);
	if (i == 1 && obj->nb == 4)
		get_sphere_inf(obj);
	if (i == 2 && obj->nb == 5)
		get_plane_inf(obj);
	if (i == 3 && obj->nb == 7)
		get_cone_inf(obj);
	if (i == 4 && obj->nb == 7)
		get_cyl_inf(obj);
	return (true);
}

void	put_inf_to_glob(t_obj *obj)
{
	t_obj *otmp;

	if (g_global.r->objects == NULL)
		g_global.r->objects = (t_obj *)obj;
	else
	{
		otmp = g_global.r->objects;
		while (otmp->next != NULL)
			otmp = otmp->next;
		otmp->next = (t_obj *)obj;
	}
}

bool	parse_object(t_json_object *obj, unsigned long nb)
{
	t_json_array	*list;
	unsigned long	num;

	num = 0;
	if (obj->pair[nb] == NULL ||obj->pair[nb]->value->type != 3)
		return (false);
	list = (t_json_array *)obj->pair[nb]->value->ptr;
	while (num < list->nb)
	{
		add_new_obj(list, num);
		num++;
	}
	return (true);
}
