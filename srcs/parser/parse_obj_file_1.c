#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

static	bool		add_face(t_poly_obj **obj, t_vertex *v_list, char *line)
{
	t_poly_obj      *tmp;
	t_poly_obj      *new;

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

static	bool		read_line(t_poly_obj **obj, t_vertex **v_list, char *line, double size)
{
	if (line[0] == 'v')
		return (add_vertex(v_list, line, size));
	else if (line[0] == 'f' && *v_list != NULL)
		return (add_face(obj, *v_list, line));
	return (true);
}

static t_poly_obj   end_parsing(t_poly_obj *obj, int i)
{
    ft_putstr("Parsing ended at line ");
	ft_putnbr(i);
	ft_putstr("\n");
	return (obj);
}

t_poly_obj			*parse_obj(char *scene_line, double size)
{
	t_poly_obj      *obj;
	t_vertex        *v_list;
	int             fd;
	char            *line;
	int             i;

	obj = NULL;
	v_list = NULL;
	fd = open(scene_line, O_RDONLY);
	if (fd == -1)
		ft_exit("Couldn't open obj file", 1);
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (read_line(&obj, &v_list, line, size) == false)
		{
			free(line);
			if (v_list != NULL)
				free_vlist(&v_list);
			return (end_parsing(obj, i));
		}
		i++;
		free(line);
	}
	free_vlist(&v_list);
	return (obj);
}