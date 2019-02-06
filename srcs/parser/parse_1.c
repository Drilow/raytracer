/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:54:44 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:46:52 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>

extern t_global g_global;

bool		check_arr(t_json_array *arr)
{
	unsigned long	i;

	i = 0;
	while (i < arr->nb)
	{
		if (arr->value[i]->type == 5)
			i++;
		else
			return (false);
	}
	return (true);
}

bool		start_parse(t_json_object *obj, int type, unsigned long nb)
{
	if (type == -1)
	{
		ft_putstr("Warning : Object type not recognized :");
		ft_putendl(obj->pair[nb]->key->str);
		return (false);
	}
	if (type == 1)
		parse_light(obj, nb);
	if (type == 2)
		parse_camera(obj, nb);
	if (type == 3)
		parse_object(obj, nb);
	if (type == 4)
		parse_amblight(obj, nb);
	return (true);
}
