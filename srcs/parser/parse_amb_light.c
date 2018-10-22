/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:17:09 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/22 16:00:58 by mabessir         ###   ########.fr       */
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
}

static 	t_light			*put_info(t_json_array *arr, t_rgb *lights)
{
	int				*a;

	if (arr->nb == 3)
	{
		a = (int *)arr->value[num++]->ptr;
		lights->source->x = (double)*a;
		a = (int *)arr->value[num++]->ptr;
		lights->source->y = (double)*a;
		a = (int *)arr->value[num]->ptr;
		lights->source->z = (double)*a;
	}
	else 
	{
		lights->source->x = -30;
		lights->source->y = 150;
		lights->source->z = -100;
	}
	return (lights);
}

static	void	get_info(t_json_value *val, int i)
{
	t_json_array	*arr;
	t_rgb			alight;
	unsigned long	num;

	num = 0;
	if (val->type != array)
		return ;
	arr = (t_json_array *)val->ptr;
		alight = put_info(arr);
}

void			*parse_light(t_json_object *obj, unsigned long nb)
{
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
			get_info(ol->value[num], 1);
	}
}
