/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:13:15 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/01 16:51:58 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>


static	bool	get_obj_type(t_json_pair *pair)
{
	t_json
	if (pair->value->ptr)
}

static 	bool	get_sphere_inf(t_json_object *obj, unsigned long nb)
{
	if (obj->pair[nb]->value->type != array)
		return (false);
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
	obj = (t_json_object *) list->value[num]->ptr;
	if (cmp_chars(obj->pair[0]->key->str, "type", 0) == false)
		return (false);
	i = get_obj_type(obj->pair[0]);
	if ( )
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
	if 
	return (true);
}