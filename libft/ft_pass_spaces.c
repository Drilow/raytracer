/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:34:24 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/15 11:50:18 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pass_spaces(t_json_file *file)
{
	while (ft_isspace(file->str[file->pos]) && file->pos < file->len)
		++file->pos;
}

void	pass_items(t_json_file *f)
{
	if (f->str[f->pos] == '"' && ft_isalpha(f->str[f->pos]) == 0)
		f->pos += (f->str[f->pos] == '"' && f->pos < f->len) ? 1 : 0;
	f->pos += (f->str[f->pos] == ',' && f->pos < f->len) ? 1 : 0;
}
