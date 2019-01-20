/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:45:27 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/19 15:11:58 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBJSON_H
# define LIBJSON_H
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_json_value	t_json_value;

typedef enum				e_json_value_type
{
	none = 0,
	null = 1,
	boolean = 2,
	array = 3,
	object = 4,
	integer = 5,
	number = 6,
	string = 7
}							t_json_value_type;

typedef struct				s_json_file
{
	const char			*str;
	unsigned long		len;
	unsigned long		pos;
	unsigned long		index;
}							t_json_file;

struct						s_json_value
{
	t_json_value		*parent;
	t_json_value_type	type;
	void				*ptr;
}							;

typedef struct				s_json_string
{
	char				*str;
	unsigned long		len;
}							t_json_string;

typedef struct				s_json_array
{
	unsigned long		nb;
	t_json_value		**value;
}							t_json_array;

typedef struct				s_json_pair
{
	t_json_string		*key;
	t_json_value		*value;
}							t_json_pair;

typedef struct				s_json_object
{
	unsigned long		nb;
	t_json_pair			**pair;
}							t_json_object;

t_json_value				*json_init(char *str);

t_json_value				*new_json_value(t_json_file *file,
t_json_value *parent);

t_json_value				*new_boolean(t_json_file *file,
t_json_value *parent);

t_json_value				*init_number(t_json_file *file,
t_json_value_type type, t_json_value *parent);

t_json_value				*ft_fill_json_value(t_json_value *parent,
t_json_value_type type, void *ptr);

t_json_value				*new_string(t_json_file *file,
t_json_value *parent);

t_json_string				*make_new_string(t_json_file *file);

t_json_value_type			get_json_value_type(t_json_file *file);

t_json_value				*new_object(t_json_file *f, t_json_value *parent,
unsigned long index);

t_json_value				*new_array(t_json_file *file, t_json_value *parent,
unsigned long index);

void						json_free(t_json_value *val);

void						json_free_string(t_json_string *string);

void						json_free_array(t_json_array *array);

void						json_free_object(t_json_object *obj);

void						json_free_pair(t_json_pair *pair);

#endif
