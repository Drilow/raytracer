/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:17:00 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/29 15:18:58 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

static	int		check_key(char *str)
{
	if (cmp_chars(str, "source", 0))
		return (1);
	if (cmp_chars(str, "color", 0))
		return (2);
	return (0)
}

static 	t_light			*put_info(t_json_array *arr, t_light *lights)
{
	int				*a;
	unsigned long	*num;

	num = 0;
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
	t_light			*lights;
	t_light			*ltmp;
	unsigned long	num;

	num = 0;
	if (val->type != array)
		return ;
	arr = (t_json_array *)val->ptr;
	if (!(lights = (t_light *)malloc(sizeof(t_light))))
		return ;
	((t_light *)lights)->next = NULL;
	if (i == 1)
		lights = put_info(arr);
	if (i == 2)
		lights->color = get_obj_color(val);
	if (g_global.r->lights == NULL)
		g_global.r->lights = lights;
	else
	{
		ltmp = g_global.r->lights;
		while (ltmp->next != NULL)
			ltmp = ltmp->next;
		ltmp->next = lights;
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
			get_info(ol->value[num], 1);
		if (check_key(ol->value[num]) == 2)
			get_info(ol->value[num], 2);
	}
}
