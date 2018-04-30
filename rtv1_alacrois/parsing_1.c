/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 02:57:56 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/29 17:33:07 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	if (cmp_chars(s, "//", 0) == true)
		return (-2);
	return (-1);
}

static t_obj	*malloc_object(int type)
{
	t_obj		*o;

	o = (t_obj *)ft_malloc(sizeof(t_obj));
	if (type == 1)
		o->obj = (t_sphere *)ft_malloc(sizeof(t_sphere));
	else if (type == 2)
		o->obj = (t_plane *)ft_malloc(sizeof(t_plane));
	else if (type == 3)
		o->obj = (t_cone *)ft_malloc(sizeof(t_cone));
	else if (type == 4)
		o->obj = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	o->type = type;
	o->next = NULL;
	return (o);
}

static void		add_to_list(t_rtv1 *r, void *o, int otype)
{
	t_obj		*otmp;
	t_light		*ltmp;

	if (otype != 0)
	{
		if (r->objects == NULL)
			r->objects = (t_obj *)o;
		else
		{
			otmp = r->objects;
			while (otmp->next != NULL)
				otmp = otmp->next;
			otmp->next = (t_obj *)o;
		}
		return ;
	}
	if (r->lights == NULL)
		r->lights = (t_light *)o;
	else
	{
		ltmp = r->lights;
		while (ltmp->next != NULL)
			ltmp = ltmp->next;
		ltmp->next = (t_light *)o;
	}
}

static t_bool	read_line(t_rtv1 *r, char *line)
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
		return (set_camera(r, line));
	if (obj_type == 0)
	{
		new = (t_light *)ft_malloc(sizeof(t_light));
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
	if (obj_type != 6 && get_obj(line, new, &index, obj_type) == false)
		return (false);
	add_to_list(r, new, obj_type);
	return (true);
}

t_bool			parse(t_rtv1 *r, char *file)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	r->objects = NULL;
	r->lights = NULL;
	while (ft_gnl(fd, &line) == 1)
	{
		if (read_line(r, line) == false)
			usage("Error : invalid file.");
		free(line);
	}
	return (true);
}
