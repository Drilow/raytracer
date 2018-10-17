/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:12:59 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/17 13:47:47 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "includes/json.h"

t_json_value	*new_json_value(t_json_file *file, t_json_value *parent)
{
	t_json_value_type	type;
	unsigned long		index;

	index = 0;
	while (ft_isspace(file->str[file->pos]))
		file->pos++;
	type = get_json_value_type(file);
	if (type == number)
		return (init_number(file, number, parent));
	if (type == integer)
		return (init_number(file, integer, parent));
	if (type == boolean)
		return (new_boolean(file, parent));
	if (type == null && (file->pos += 4))
		return (ft_fill_json_value(parent, null, NULL));
	if (type == string)
		return (new_string(file, parent));
	if (type == object)
		return (new_object(file, parent, index));
	if (type == array)
		return (new_array(file, parent, index));
	return (NULL);
}
