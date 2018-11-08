/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_bool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 11:36:22 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/08 18:33:52 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "includes/json.h"

t_json_value	*new_boolean(t_json_file *file, t_json_value *parent)
{
	void	*new_bool;
	int		*aswr;

	new_bool = NULL;
	if (check_bool(file) == 1 && (file->pos += 4))
	{
		aswr = 1;
		new_bool = (void *)&aswr;
		return (ft_fill_json_value(parent, boolean, new_bool));
	}
	else if (check_bool(file) == 2 && (file->pos += 5))
	{
		aswr = 0;
		new_bool = (void *)&aswr;
		return (ft_fill_json_value(parent, boolean, new_bool));
	}
	return (new_bool);
}
