/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:54:44 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/29 16:08:49 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

bool		start_parse(t_json_obj *obj, int type, unsigned long nb)
{
	if (type == -1)
	{
		ft_putstr("Warning : Object type not recognized :");
		ft_putendl(obj->pair[nb]->key->str);
		return (false);
	}
	if (type == 0)
		parse_light(obj, nb);
	if (type == 5)
		parse_camera(obj, nb);
	if (type == 7)
		parse_ambient_light(obj, nb);
}