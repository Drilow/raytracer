/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:17:09 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/08 11:38:21 by mabessir         ###   ########.fr       */
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
	return (0);
}

static	void	get_info(t_json_value *val)
{
	t_rgb			alight;

	alight = get_obj_color(val);
	g_global.r->ambient_light = alight;
}

void			*parse_amblight(t_json_object *obj, unsigned long nb)
{
	t_json_object	*ol;
	unsigned long	num;

	num = 0;
	if (obj->pair[nb]->value->type != 4)
		return (NULL);
	if((ol = (t_json_object *)obj->pair[nb]->value->ptr) == NULL)
		return (NULL);
	if (check_key(ol->pair[num]->key->str) == 1)
		get_info(ol->pair[num]->value);
	return (NULL);
}
