/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 15:53:45 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/29 13:45:51 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_null(t_json_file *file)
{
	if (file->pos + 3 < file->len)
	{
		if ((file->str[file->pos] == 'n' || file->str[file->pos] == 'N')
			&& (file->str[file->pos + 1] == 'u' || file->str[file->pos + 1]
				== 'U')
			&& (file->str[file->pos + 2] == 'l' || file->str[file->pos + 2]
				== 'L')
			&& (file->str[file->pos + 3] == 'l' || file->str[file->pos + 3]
				== 'L'))
			return (1);
	}
	return (0);
}
