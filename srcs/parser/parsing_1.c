/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 02:57:56 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/15 11:58:01 by mabessir         ###   ########.fr       */
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
		return (1);
	if (cmp_chars(s, "camera", 0) == true)
		return (2);
	if (cmp_chars(s, "objects", 0) == true)
        return (3);
	if (cmp_chars(s, "cube", 0) == true)
		return (5);
	if (cmp_chars(s, "tetrahedron", 0) == true)
		return (6);
	if (cmp_chars(s, "ambientlight", 0) == true)
        return (4);
	if (cmp_chars(s, "//", 0) == true)
		return (-2);
	ft_putendl(s);
	return (-1);
}

t_obj	*malloc_object(int type)
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
/*
static void		add_to_list(void *o, int otype)
{
	t_obj		*otmp;
	t_light		*ltmp;

	if (otype != 0)
	{
		if (g_global.r->objects == NULL)
			g_global.r->objects = (t_obj *)o;
		else
		{
			otmp = g_global.r->objects;
			while (otmp->next != NULL)
				otmp = otmp->next;
			otmp->next = (t_obj *)o;
		}
		return ;
	}
	if (g_global.r->lights == NULL)
		g_global.r->lights = (t_light *)o;
	else
	{
		ltmp = g_global.r->lights;
		while (ltmp->next != NULL)
			ltmp = ltmp->next;
		ltmp->next = (t_light *)o;
	}
}

static bool	set_ambient_light(char *line)
{
	int		index;
	t_rgb	alight;

	index = 0;
	if (get_next_nb(line, &index, NULL, &(alight.r)) == false)
		return (false);
	if (get_next_nb(line, &index, NULL, &(alight.g)) == false)
		return (false);
	if (get_next_nb(line, &index, NULL, &(alight.b)) == false)
		return (false);
	if (get_next_nb(line, &index, NULL, &(alight.trans)) == false)
		return (false);
	g_global.r->ambient_light = alight;
	return (true);
}
*/
/*
static bool	read_line(char *line)
{
	int			obj_type;
	void		*new;
	int			index;

	obj_type = get_object_type(line);
	if (obj_type == -1)
		return (false);
	else if (obj_type == -2)
		return (true);
	else if (obj_type == 5)
		return (set_camera(line));
	else if (obj_type == 7)
		return (set_ambient_light(line));
	if (obj_type == 0)
	{
	  if (!(new = (t_light *)malloc(sizeof(t_light))))
	    exit(1);
		((t_light *)new)->next = NULL;
	}
	else
		new = malloc_object(obj_type);
	index = 0;

	if (obj_type == 6)
	{
//		((t_obj *)new)->obj = parse_obj(line + (sizeof(char) * 4));
		((t_obj *)new)->obj = parse_obj(line);
		index = 4;
		while (line[index] != ' ')
			index++;
		if (((t_obj *)new)->obj == NULL)
			printf("((t_obj *)new)->obj == NULL\n");
		if (((t_obj *)new)->obj == NULL || get_next_rpoint(line, &(((t_obj *)new)->position), &index) == false)
			return (false);
		((t_obj *)new)->color = ft_rgb(170, 130, 120, 0);
		set_obj((t_obj *)new);
//		return (true);
	}
*/
	/*
	if (obj_type != 6 && get_obj(line, new, &index, obj_type) == false)
		return (false);
	*//*
	if (get_obj(line, new, &index, obj_type) == false)
		return (false);
	add_to_list(new, obj_type);
	return (true);
}*/
bool			parse(char *file)
{
	int				fd;
	char			*str;
	//char			*line;
	t_json_value	*val;
	unsigned long	nb;
	t_json_object	*obj;

	nb = 0;
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
	obj = (t_json_object *)val->ptr;
	while (nb < obj->nb)
	{
		start_parse(obj, get_object_type(obj->pair[nb]->key->str), nb);
		nb++;
	}
	/*while (get_next_line(fd, &line) == 1)
	{
		if (read_line(line) == false)
			usage("Error : invalid file.", 1);
	
		//printf("%s\n", line);
		free(line);
	}*/
	close(fd);
	return (true);
}
