/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:49:08 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/23 18:57:54 by mabessir         ###   ########.fr       */
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
	if (cmp_chars(str, "pos", 0))
		return (1);
	if (cmp_chars(str, "angle", 0))
		return (2);
	return (0)
}

void		*parse_camera(t_json_object *obj, unsigned long nb)
{
	t_json_object	*o;
	unsigned long	num;

	num = 0;
	if (obj->pair[nb]->value->type != 4)
		return (NULL);
	if((o = (t_json_object *)obj->pair[nb]->value->ptr) == NULL)
		return (NULL);
	while (num++ < o->nb)
	{
		if ()
	}
}