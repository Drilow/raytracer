/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:43:54 by mabessir          #+#    #+#             */
/*   Updated: 2019/01/22 18:50:34 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

static	bool		add_face(t_poly_obj **obj, t_vertex *v_list, char *line)
{
	t_poly_obj		*tmp;
	t_poly_obj		*new;

	new = pmalloc_po();
	if (parse_face(new, line, v_list) == false)
		return (false);
	if (*obj == NULL)
		*obj = new;
	else
	{
		tmp = *obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (true);
}

static	bool		read_line(t_poly_obj **obj, t_vertex **v_list, \
								char *line, double size)
{
	if (line[0] == 'v')
		return (add_vertex(v_list, line, size));
	else if (line[0] == 'f' && *v_list != NULL)
		return (add_face(obj, *v_list, line));
	return (true);
}

static bool			end_parsing(int i, t_vertex *v_list, char *line)
{
	free(line);
	if (v_list != NULL)
		free_vlist(&v_list);
	ft_putstr("Parsing ended at line ");
	ft_putnbr(i);
	ft_putstr("\n");
	return (false);
}

bool				validate_obj(t_rpoint pos, double size, char *path, \
									t_obj *o)
{
	t_poly_obj		*obj;
	t_vertex		*v_list;
	int				fd;
	char			*line;
	int				i;

	ft_putendl("==> validate_obj");
	obj = NULL;
	o->obj = NULL;
	v_list = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Couldn't open obj file", 1);
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (read_line(&obj, &v_list, line, size) == false)
			return (end_parsing(i, v_list, line));
		i++;
		free(line);
	}
	free_vlist(&v_list);
	o->obj = obj;
	o->position = pos;
	o->size = size;
	return (true);
}
