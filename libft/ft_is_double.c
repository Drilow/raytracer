/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:48:39 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/15 12:07:50 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isedigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_is_double(t_json_file *file)
{
	unsigned long pos;

	pos = file->pos;
	if (file->str[pos] == '+' || file->str[pos] == '-')
	{
		pos++;
		if (file->str[pos] == '+' || file->str[pos] == '-')
			return (2);
	}
	while (pos < file->len)
	{
		if (ft_isedigit(file->str[pos]))
			pos++;
		else if (file->str[pos] == '.')
			return (1);
		else if (file->str[pos] == 'e')
			return (1);
		else if (file->str[pos] == 'E')
			return (1);
		else
			return (0);
	}
	return (0);
}
