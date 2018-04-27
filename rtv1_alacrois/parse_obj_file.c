/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:46:46 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/27 17:40:01 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_poly_obj	*malloc_po(void)
{
  t_poly_obj		*obj;

  obj = (t_poly_obj *)ft_malloc(sizeof(t_poly_obj));
  obj->next = NULL;
  return (obj);
}

static t_vertex		*malloc_vertex(void)
{
  t_vertex			*v;

  v = (t_vertex *)ft_malloc(sizeof(t_vertex));
  v->next = NULL;
  return (v);
}

static void			free_vlist(t_vertex **v_list)
{
  t_vertex			*tmp;
  t_vertex			*tmp_next;

  tmp = *v_list;
  while (tmp != NULL)
	{
	  tmp_next = tmp->next;
	  free(tmp);
	  tmp = tmp_next;
	}
}

static t_bool	get_next_double(char *line, int *index, double *a)
{
  double		sign;
  double		tmp;
  int			digit_index;

  sign = 1;
  tmp = 0;
//  ft_putendl("1.1");
  while (line[*index] != '-' && ft_isdigit(line[*index]) == 0 && \
		 line[*index] != '\0')
	(*index)++;
//  ft_putendl("1.2");
  if (line[*index] == '-')
	{
	  sign = -1;
	  (*index)++;
	}
//  ft_putendl("1.3");
  if (line[*index] == '\0')
	return (false);
  if (ft_isdigit(line[*index]) == 0)
	return (get_next_double(line, index, a));
//  ft_putendl("1.4");
  while (ft_isdigit(line[*index]) == 1)
	{
//		ft_putendl("1.4.1");
	  tmp = (tmp * 10) + (double)(line[*index] - '0');
	  (*index)++;
	}
//  ft_putendl("1.4.2");
  if (line[*index] != '.')
	{
	  *a = tmp * sign;
//	  ft_putendl("1.4.3");
	  return (true);
	}
//  ft_putendl("1.5");
  (*index)++;
  digit_index = 1;
  while (ft_isdigit(line[*index]) == 1)
	{
	  tmp = tmp + ((double)(line[*index] - '0') / pow(10, digit_index));
	  (*index)++;
	  digit_index++;
	}
//  ft_putendl("6");
  *a = tmp * sign;
  return (true);
}

static t_bool	parse_vertex(t_vertex *v, char *line)
{
  int			index;

  index = 0;
  if (get_next_double(line, &index, &(v->p.x)) == false)
	return (false);
  if (get_next_double(line, &index, &(v->p.y)) == false)
	return (false);
  if (get_next_double(line, &index, &(v->p.z)) == false)
	return (false);
  return (true);
}

static t_bool	add_vertex(t_vertex **v_list, char *line)
{
  t_vertex		*tmp;
  t_vertex		*new;

//  ft_putendl("add_vertex");
  new = malloc_vertex();
  if (parse_vertex(new, line) == false)
	return (false);
  if (*v_list == NULL)
	*v_list = new;
  else
	{
	  tmp = *v_list;
	  while (tmp->next != NULL)
		tmp = tmp->next;
	  tmp->next = new;
	}
  return (true);
}

static t_bool	get_vertex(t_vertex *v_list, int position, t_vertex *v)
{
  t_vertex		*tmp;
  int			index;

  tmp = v_list;
  index = 0;
  while (tmp != NULL)
	{
	  index++;
	  if (position == index)
		{
		  v->p = tmp->p;
		  return (true);
		}
	  tmp = tmp->next;
	}
  return (false);
}

static t_bool	parse_face(t_poly_obj *face, char *line, t_vertex *v_list)
{
  int			line_index;
  double		v_index;
  t_vertex		*vertices;
  int			v_nb;

//  ft_putendl("1");
  v_index = 0;
  line_index = 0;
  vertices = NULL;
  v_nb = 0;
  while (get_next_double(line, &line_index, &v_index) == true)
	{
	  v_nb++;
//	  ft_putendl("2");
	  if (vertices == NULL)
		{
//			ft_putendl("3");
		  vertices = malloc_vertex();
		  face->vertices = vertices;
		  if (get_vertex(v_list, (int)v_index, vertices) == false)
			return (false);
		}
	  else
		{
//			ft_putendl("4");
		  while (vertices->next != NULL)
			vertices = vertices->next;
//		  ft_putendl("4.1");
		  vertices->next = malloc_vertex();
//		  ft_putendl("4.2");
		  if (get_vertex(v_list, (int)v_index, vertices->next) == false)
			  return (false);
//		  ft_putendl("4.3");
		}
	}
//  ft_putendl("5");
  if (v_nb < 3)
	return (false);
  return (true);
}

static t_bool	add_face(t_poly_obj **obj, t_vertex *v_list, char *line)
{
  t_poly_obj   	*tmp;
  t_poly_obj	*new;

//  ft_putendl("add_face");
  new = malloc_po();
//  ft_putendl("1");
  if (parse_face(new, line, v_list) == false)
	return (false);
//  ft_putendl("2");
  if (*obj == NULL)
	*obj = new;
  else
	{
//		ft_putendl("3");
	  tmp = *obj;
	  while (tmp->next != NULL)
		tmp = tmp->next;
	  tmp->next = new;
	}
//  ft_putendl("4");
  return (true);
}



static t_bool	read_line(t_poly_obj **obj, t_vertex **v_list, char *line)
{
  if (line[0] == 'v')
	return (add_vertex(v_list, line));
  else if (line[0] == 'f' && *v_list != NULL)
	return (add_face(obj, *v_list, line));
  return (false);
}

static char		*get_file_name(char *line)
{
	char		*file;
	int			index;
	int			len;

	index = 4;
	len = 0;
	while (line[index] != ' ')
		index++;
	len = index - 4;
	file = (char *)ft_malloc(sizeof(char) * (len + 1));
	index = 0;
	while (index < len)
	{
		file[index] = line[index + 4];
		index++;
	}
	file[index] = '\0';
	return (file);
}

t_poly_obj		*parse_obj(char *scene_line)
{
  t_poly_obj	*obj;
  t_vertex		*v_list;
  int			fd;
  char			*file;
  char			*line;
  int			i;

  obj = NULL;
  v_list = NULL;
//  ft_putendl("1");
  file = get_file_name(scene_line);
  // ft_putendl("2");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit("Couldn't open obj file");
//		return (NULL);
	i = 0;
	while (ft_gnl(fd, &line) == 1)
	{
	  if (read_line(&obj, &v_list, line) == false)
	  {
//	  return (NULL);
		  free(line);
		  if (v_list != NULL)
			  free_vlist(&v_list);
//		  printf("Lalalala\n");
		  ft_putstr("Parsing ended at line ");
		  ft_putnbr(i);
		  ft_putstr("\n");
		  return (obj);
	  }
	  i++;
//	  ft_putendl("2.2");
//	  printf("%d\n", i++);
		free(line);
	}
//	ft_putendl("3");
	free_vlist(&v_list);
  return (obj);
}
