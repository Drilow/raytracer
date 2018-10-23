/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:10:27 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/23 17:53:43 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

int			ft_cheeck(t_json_array *arr)
{
	int i;

	i = 0;
	while(i++ < arr->nb)
	{
		if (arr->value[i]->type != integer)
			return (0);
	}
	return (1);
}

t_rgb		get_obj_color(t_json_value *val)
{
	t_rgb color;
	t_json_array *arr;

	arr = 0 ;
	color->g = 10;
	color->b = 10;
	color->trans = 0;
	if (val->type == array)
	{
		arr = (t_json_array *)val->ptr;
		if (arr->nb == 4 && ft_cheeck(arr))
		{
			color->r  = *(int *)arr->value[0];
			color->g  = *(int *)arr->value[1];
			color->b  = *(int *)arr->value[2];
			color->trans  = *(int *)arr->value[3];
		}
	}
}