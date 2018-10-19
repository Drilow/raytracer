/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:54:44 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/19 16:34:21 by mabessir         ###   ########.fr       */
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

static int		get_object_type(char *s)
{
	if (cmp_chars(s, "light", 0) == true)
		return (0);
	if (cmp_chars(s, "sphere", 0) == true)
		return (1);
	if (cmp_chars(s, "plane", 0) == true)
		return (2);
	if (cmp_chars(s, "cone", 0) == true)
		return (3);
	if (cmp_chars(s, "cylinder", 0) == true)
		return (4);
	if (cmp_chars(s, "camera", 0) == true)
		return (5);
	if (cmp_chars(s, "obj", 0) == true)
        return (6);
	if (cmp_chars(s, "cube", 0) == true)
		return (66);
	if (cmp_chars(s, "tetrahedron", 0) == true)
		return (67);
	if (cmp_chars(s, "ambient light", 0) == true)
        return (7);
	if (cmp_chars(s, "//", 0) == true)
		return (-2);
	ft_putendl(s);
	return (-1);
}

bool		start_parse(t_json_obj *obj, unsigned long type, unsigned long nb)
{
	if (type == -1)
	{
		ft_putendl("Warning : Object type not recognized")
		return (false);
	}
	if (type == 0)
		parse_light(obj, nb);
}