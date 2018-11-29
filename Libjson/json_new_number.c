/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:58:59 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/29 13:42:36 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "includes/json.h"

static void				jump_number(t_json_file *file)
{
	if (file->str[file->pos] == '+' || file->str[file->pos] == '-')
		file->pos++;
	while (ft_isdigit(file->str[file->pos]))
		++file->pos;
	if (file->str[file->pos] == '.')
	{
		file->pos++;
		while (ft_isdigit(file->str[file->pos]))
			++file->pos;
	}
	if (file->str[file->pos] == 'e' || file->str[file->pos] == 'E')
	{
		file->pos++;
		if (file->str[file->pos] == '+' || file->str[file->pos] == '-')
			file->pos++;
		while (ft_isdigit(file->str[file->pos]))
			file->pos++;
	}
}

static	t_json_value	*ft_number(t_json_file *file, t_json_value *num)
{
	double *numb;

	num->type = number;
	if ((num->ptr = malloc(sizeof(double))) == NULL)
		return (NULL);
	*(double *)(num->ptr) = ft_atof(&file->str[file->pos]);
	numb = (double *)num->ptr;
	return (num);
}

static	t_json_value	*ft_integer(t_json_file *file, t_json_value *num)
{
	num->type = integer;
	if ((num->ptr = malloc(sizeof(int))) == NULL)
		return (NULL);
	*(int *)(num->ptr) = ft_atoi(&file->str[file->pos]);
	return (num);
}

t_json_value			*init_number(t_json_file *file, t_json_value_type type,
t_json_value *parent)
{
	t_json_value *num;

	if (file->str == NULL || file->pos >= file->len
		|| (ft_isdigit(file->str[file->pos]) != 1 && file->str[file->pos] != '-'
		&& file->str[file->pos] != '+'))
		return (NULL);
	if ((num = (t_json_value *)malloc(sizeof(t_json_value))) == NULL)
		return (NULL);
	if (type == number)
		ft_number(file, num);
	if (type == integer)
		ft_integer(file, num);
	num->parent = parent;
	jump_number(file);
	return (num);
}
