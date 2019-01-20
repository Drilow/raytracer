/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_fill_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 15:56:34 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/09 13:56:03 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/json.h"

t_json_value	*ft_fill_json_value(t_json_value *parent,
t_json_value_type type, void *ptr)
{
	t_json_value *val;

	if ((val = (t_json_value*)malloc(sizeof(t_json_value))) == NULL)
		return (NULL);
	val->type = type;
	val->parent = parent;
	val->ptr = ptr;
	return (val);
}
