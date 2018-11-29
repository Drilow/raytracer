/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:07:51 by mabessir          #+#    #+#             */
/*   Updated: 2018/11/29 13:42:15 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "includes/json.h"

t_json_string	*make_new_string(t_json_file *file)
{
	t_json_string *str;
	unsigned long i;

	if (file->str == NULL || file->pos >= file->len
		|| file->str[file->pos] != '"')
		return (NULL);
	i = file->pos + 1;
	while (i < file->len && file->str[i] != '\0' && file->str[i] != '"')
		i++;
	if (i == file->len || file->str[i] == '\0')
		return (NULL);
	if ((str = (t_json_string *)malloc(sizeof(t_json_string))) == NULL)
		return (NULL);
	str->len = i - file->pos - 1;
	if ((str->str = ft_strndup(&file->str[file->pos] + 1, str->len)) == NULL)
		return (NULL);
	file->pos += str->len + 1;
	file->pos += (file->str[file->pos] == '"' && file->pos < file->len) ? 1 : 0;
	return (str);
}

t_json_value	*new_string(t_json_file *file, t_json_value *parent)
{
	t_json_string *new_string;

	if ((new_string = make_new_string(file)) == NULL)
		return (NULL);
	return (ft_fill_json_value(parent, string, new_string));
}
