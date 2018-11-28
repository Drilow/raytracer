/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectsfn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:32:59 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/28 15:34:14 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

bool	get_inf(t_obj *o, t_json_value *val)
{
	int				*a;
	t_json_array	*arr;

	if (val == NULL)
		return (false);
	if (val->type == 3)
	{
		arr = (t_json_array *)val->ptr;
		if (!check_arr(arr) && arr->nb != 3)
			return (false);
		a = (int *)arr->value[0]->ptr;
		o->position.x = (double)*a;
		a = (int *)arr->value[1]->ptr;
		o->position.y = (double)*a;
		a = (int *)arr->value[2]->ptr;
		o->position.z = (double)*a;
	}
	return (true);
}

bool	verif_infinite(t_obj *o, t_json_value *val)
{
	bool		a;
	t_cylinder	*c;
	t_cone		*co;

	a = true;
	c = 0;
	co = 0;
	if (val == NULL)
		return (false);
	if (o->type == 3 && val->type == 2)
	{
		co = (t_cone *)o->obj;
		a = (bool)val->ptr;
		co->infinite = a;
	}
	else if (o->type == 4 && val->type == 2)
	{
		c = (t_cylinder *)o->obj;
		a = (bool)val->ptr;
		c->infinite = a;
	}
	else
		return (false);
	return (true);
}