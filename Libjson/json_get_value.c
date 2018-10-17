/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_get_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 13:40:24 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/17 13:35:02 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "includes/json.h"

void	*json_get_values(t_json_value *value, int type)
{
	bool			*boo;
	t_json_string	*string;

	boo = 0;
	string = 0;
	if (type > 0 && type <= 2)
	{
		if (type == 1)
			return ((void *)null);
		if (type == 2)
		{
			boo = (bool *)value->ptr;
			ft_free(value->ptr);
			ft_free(value);
			return ((void *)boo);
		}
	}
	else if (type == 7)
	{
		string = (t_json_string *)value->ptr;
		ft_free(value->ptr);
		ft_free(value->ptr);
		return ((void *)string);
	}
	return ((void *)none);
}

void	*json_get_big_values(t_json_value *value, int type)
{
	t_json_array	*array;
	t_json_object	*object;

	array = 0;
	object = 0;
	if (type == 3)
	{
		array = (t_json_array *)value->ptr;
		ft_free(value->ptr);
		ft_free(value);
		return ((void *)array);
	}
	if (type == 4)
	{
		object = (t_json_object *)value->ptr;
		ft_free(value->ptr);
		ft_free(value);
		return ((void *)object);
	}
	return ((void *)-1);
}

void	*json_get_num_values(t_json_value *value, int type)
{
	int		*a;
	double	*b;

	a = 0;
	b = 0;
	if (type == 4)
	{
		a = (int *)value->ptr;
		ft_free(value->ptr);
		ft_free(value);
		return ((void *)a);
	}
	if (type == 5)
	{
		b = (double *)value->ptr;
		ft_free(value->ptr);
		ft_free(value);
		return ((void *)b);
	}
	return ((void *)-1);
}
