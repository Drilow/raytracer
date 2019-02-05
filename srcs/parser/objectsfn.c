/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectsfn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:32:59 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:46:30 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

bool	get_inf(t_obj *o, t_json_value *val)
{
	int				*a;
	t_json_array	*arr;

	if (val == NULL)
		return (false);
	if (val->type == 3)
	{
		arr = (t_json_array *)val->ptr;
		if (!check_arr(arr) || arr->nb != 3)
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

bool	geet_reflex(t_json_value *val, t_obj *o)
{
	if (val == NULL)
		return (false);
	if (val->type != 5)
		return (false);
	o->reflex = *(int *)val->ptr;
	return (true);
}

t_obj	*malloc_object2(int type)
{
	t_obj	*o;

	o = NULL;
	if (!(o = (t_obj *)malloc(sizeof(t_obj))))
		ft_exit("Malloc error ('objectsfn.c' --> Ln 85)", 1);
	o->reflex = 0;
	o->obj = NULL;
	o->type = type;
	o->next = NULL;
	if (type == 1)
	{
		if (!(o->obj = (t_sphere *)malloc(sizeof(t_sphere))))
			ft_exit("Malloc error ('objectsfn.c' --> Ln 93)", 1);
	}
	else if (type == 2)
	{
		if (!(o->obj = (t_plane *)malloc(sizeof(t_plane))))
			ft_exit("Malloc error ('objectsfn.c' --> Ln 98)", 1);
	}
	return (o);
}
