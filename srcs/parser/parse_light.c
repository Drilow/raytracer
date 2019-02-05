/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:17:00 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:48:21 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

extern t_global g_global;

static	int			check_key(char *str)
{
	if (cmp_chars(str, "source", 0))
		return (1);
	if (cmp_chars(str, "color", 0))
		return (2);
	return (0);
}

static	t_light		*put_info(t_json_array *arr, t_light *lights)
{
	int				*a;
	unsigned long	num;

	num = 0;
	if (arr->nb == 3 && check_arr(arr))
	{
		a = (int *)arr->value[num++]->ptr;
		lights->source.x = (double)*a;
		a = (int *)arr->value[num++]->ptr;
		lights->source.y = (double)*a;
		a = (int *)arr->value[num]->ptr;
		lights->source.z = (double)*a;
	}
	else
	{
		lights->source.x = 0;
		lights->source.y = 0;
		lights->source.z = 0;
	}
	return (lights);
}

static void			get_info(t_json_value *val, int i, t_light *lights)
{
	t_json_array	*arr;
	unsigned long	num;

	num = 0;
	if (val->type != 3)
		return ;
	arr = (t_json_array *)val->ptr;
	if (i == 1)
		lights = put_info(arr, lights);
	if (i == 2)
		lights->color = get_obj_color(val);
}

static	void		put_light_to_glob(t_light *lights)
{
	t_light	*ltmp;

	if (g_global.r.lights == NULL)
	{
		lights->enabled = true;
		g_global.r.lights = lights;
	}
	else
	{
		lights->enabled = true;
		ltmp = g_global.r.lights;
		while (ltmp->next != NULL)
			ltmp = ltmp->next;
		ltmp->next = lights;
	}
}

void				parse_light(t_json_object *obj, unsigned long nb)
{
	t_json_object	*ol;
	unsigned long	num;
	t_light			*lights;

	num = 0;
	lights = NULL;
	ol = NULL;
	if (obj->pair[nb]->value->type != 4)
		return ;
	if ((ol = (t_json_object *)obj->pair[nb]->value->ptr) == NULL)
		return ;
	if (!(lights = (t_light *)malloc(sizeof(t_light))))
		return ;
	((t_light *)lights)->next = NULL;
	while (num < ol->nb)
	{
		if (check_key(ol->pair[num]->key->str) == 1)
			get_info(ol->pair[num]->value, 1, lights);
		else if (check_key(ol->pair[num]->key->str) == 2)
			get_info(ol->pair[num]->value, 2, lights);
		num++;
	}
	put_light_to_glob(lights);
}
