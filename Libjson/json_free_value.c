/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_free_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 16:17:57 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/17 13:33:02 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/json.h"
#include "../libft/libft.h"

void	json_free_pair(t_json_pair *pair)
{
	if (pair == NULL)
		return ;
	json_free_string(pair->key);
	json_free(pair->value);
	ft_free(pair);
}

void	json_free_object(t_json_object *obj)
{
	unsigned long nb;

	if (obj == NULL || obj->pair == 0 || obj->nb == 0)
		return ;
	nb = 0;
	while (nb < obj->nb)
		json_free_pair(obj->pair[nb++]);
	ft_free(obj->pair);
	nb = 0;
	obj->nb = 0;
	ft_free(obj);
}

void	json_free_array(t_json_array *array)
{
	unsigned long nb;

	if (array == NULL || array->nb == 0)
		return ;
	nb = 0;
	while (nb < array->nb)
		json_free(array->value[nb++]);
	ft_free(array->value);
	array->nb = 0;
	ft_free(array);
}

void	json_free_string(t_json_string *string)
{
	if (string == NULL)
		return ;
	ft_free(string->str);
	string->len = 0;
	ft_free(string);
}

void	json_free(t_json_value *val)
{
	if (val == NULL)
		return ;
	if (val->type == 1 || val->type == 5 || val->type == 6)
		if (val->ptr != NULL)
			ft_free(val->ptr);
	if (val->type == 3)
		json_free_array(val->ptr);
	if (val->type == 4)
		json_free_object(val->ptr);
	if (val->type == 7)
		json_free_string((val->ptr));
	val->parent = NULL;
	val->type = none;
	ft_free(val);
}
