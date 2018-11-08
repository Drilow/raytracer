/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:54:44 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/08 18:08:09 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

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