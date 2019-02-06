/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:13:57 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:48:31 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

extern t_global g_global;

bool			prerotate(t_obj *obj, t_json_value *val, int type)
{
	t_rpoint		*t;
	t_json_array	*arr;
	int				*a;

	if (val == NULL || val->type != 3
	|| !(t = (t_rpoint *)malloc(sizeof(t_rpoint))))
		return (false);
	arr = (t_json_array *)val->ptr;
	if (arr->nb == 3 && check_arr(arr))
	{
		a = (int *)arr->value[0]->ptr;
		t->x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		t->y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		t->z = (double)*a;
	}
	else
		return (false);
	t->x = ((double)((int)t->x % 360) / 360) * (2 * PI);
	t->y = ((double)((int)t->y % 360) / 360) * (2 * PI);
	t->z = ((double)((int)t->z % 360) / 360) * (2 * PI);
	rotate_obj(obj, type, *t);
	free(t);
	return (true);
}

static	int		get_obj_type(t_json_pair *pair)
{
	t_json_string	*string;

	if (pair->value->type != 7)
		return (-1);
	string = (t_json_string *)pair->value->ptr;
	if (cmp_chars(string->str, "sphere", 0) == true)
		return (1);
	if (cmp_chars(string->str, "plane", 0) == true)
		return (2);
	if (cmp_chars(string->str, "cone", 0) == true)
		return (3);
	if (cmp_chars(string->str, "cylinder", 0) == true)
		return (4);
	if (cmp_chars(string->str, "cube", 0) == true)
		return (5);
	if (cmp_chars(string->str, "tetrahedron", 0) == true)
		return (6);
	if (cmp_chars(string->str, "polyobject", 0) == true)
		return (7);
	if (cmp_chars(string->str, "pyramide", 0) == true)
		return (8);
	if (cmp_chars(string->str, "dodeca", 0) == true)
		return (9);
	return (-1);
}

static	bool	add_new_obj(t_json_array *list, unsigned long num)
{
	t_json_object		*obj;
	int					i;
	static t_check_obj	check[9] = {{&get_sphere_inf, 5},
	{&get_plane_inf, 6}, {&get_cone_inf, 8}, {&get_cyl_inf, 8},
	{&get_cube_inf, 6}, {&get_tetra_inf, 6}, {&get_poly_objinf, 7},
	{&get_pyra_inf, 7}, {&get_dod_inf, 6}};

	if (list->value[num] == NULL || list->value[num]->type != 4)
		return (false);
	obj = (t_json_object *)list->value[num]->ptr;
	if (obj->nb > 8)
		return (false);
	if (cmp_chars(obj->pair[0]->key->str, "type", 0) == false)
		return (false);
	if ((i = get_obj_type(obj->pair[0])) == -1)
		return (false);
	if (check[i - 1].i == obj->nb)
	{
		if (check[i - 1].f(obj) == false)
			return (false);
	}
	return (true);
}

void			put_inf_to_glob(t_obj *obj)
{
	t_obj *otmp;

	if (g_global.r.objects == NULL)
	{
		obj->next = NULL;
		obj->enabled = true;
		g_global.r.objects = (t_obj *)obj;
	}
	else
	{
		obj->next = NULL;
		obj->enabled = true;
		otmp = g_global.r.objects;
		while (otmp->next != NULL)
			otmp = otmp->next;
		otmp->next = (t_obj *)obj;
	}
}

bool			parse_object(t_json_object *obj, unsigned long nb)
{
	t_json_array	*list;
	unsigned long	num;

	num = 0;
	if (obj->pair[nb] == NULL || obj->pair[nb]->value->type != 3)
		return (false);
	list = (t_json_array *)obj->pair[nb]->value->ptr;
	while (num < list->nb)
	{
		add_new_obj(list, num);
		num++;
	}
	return (true);
}
