/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 02:57:56 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/29 10:43:07 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

static	int		get_object_type(char *s)
{
	if (cmp_chars(s, "light", 0) == true)
		return (1);
	if (cmp_chars(s, "camera", 0) == true)
		return (2);
	if (cmp_chars(s, "objects", 0) == true)
		return (3);
	if (cmp_chars(s, "ambientlight", 0) == true)
		return (4);
	ft_putendl(s);
	return (-1);
}

t_obj			*malloc_object(int type)
{
	t_obj		*o;

	if (!(o = (t_obj *)malloc(sizeof(t_obj))))
		exit(1);
	if (type == 1)
		o->obj = (t_sphere *)malloc(sizeof(t_sphere));
	else if (type == 2)
		o->obj = (t_plane *)malloc(sizeof(t_plane));
	else if (type == 3)
		o->obj = (t_cone *)malloc(sizeof(t_cone));
	else if (type == 4)
		o->obj = (t_cylinder *)malloc(sizeof(t_cylinder));
	o->type = type;
	o->next = NULL;
	return (o);
}

bool			get_started(t_json_value *val)
{
	t_json_object	*obj;
	unsigned long	nb;

	nb = 0;
	obj = (t_json_object *)val->ptr;
	while (nb < obj->nb)
	{
		if (start_parse(obj,
			get_object_type(obj->pair[nb]->key->str), nb) == false)
			return (false);
		nb++;
	}
	return (true);
}

bool			parse(char *file)
{
	int				fd;
	char			*str;
	t_json_value	*val;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	g_global.r->objects = NULL;
	g_global.r->lights = NULL;
	g_global.r->ambient_light = ft_rgb(0, 0, 0, 0);
	str = ft_readfile(fd, file);
	if ((val = json_init(str)) == NULL)
	{
		ft_putendl("Parse failed.");
		ft_free(str);
		return (false);
	}
	ft_free(str);
	if (get_started(val) == false)
		return (false);
	close(fd);
	return (true);
}
