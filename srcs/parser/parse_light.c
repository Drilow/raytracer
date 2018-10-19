/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:17:00 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/19 18:29:34 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>
#include <stdio.h>

extern t_global g_global;

static	int		check_key(char *str)
{
	if (cmp_chars(str, "source", 0))
		return (1);
	if (cmp_chars(str, "color", 0))
		return (2);
	return (0)
}

static	void	get_info(t_json_value *val, int i)
{
	t_json_array	*arr;
	t_light			*lights;
	unsigned long	num;
	t_json_value	*tval;

	num = 0;
	val = 0;
	if (val->type != array)
		return (NULL);
	arr = (t_json_array *)val->ptr;
	if (i = 1)
	{
		while (num++ < arr->nb
		&& (arr->value[num]->type == number || arr->value[num] == integer))
		{
			tval = (t_json_value *)arr->value[num];
			
		}
	}
}

void			*parse_light(t_json_object *obj, unsigned long nb)
{
	t_json_light	*l;
	t_json_object	*ol;
	unsigned long	num;

	num = 0;
	if (obj->pair[nb]->value->type != 4)
		return (NULL);
	if((ol = (t_json_object *)obj->pair[nb]->value->ptr) == NULL)
		return (NULL);
	while (num++ < ol->nb)
	{
		if (check_key(ol->value[num]) == 1)
		{
			get_info(ol->value[num], 1);
		}
	}
}
