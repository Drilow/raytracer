/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 15:50:36 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/15 17:15:14 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/json.h"
#include "../libft/libft.h"

unsigned long	get_array_size(t_json_file *file, unsigned long pos)
{
	unsigned long cou;
	unsigned long *c;

	c = (unsigned long[4]){(file->str[file->pos++] == '['), 0, 0, 0};
	pass_spaces(file);
	cou = 1;
	if (file->str[pos] == ']')
		return (0);
	while (pos < file->len && c[0])
	{
		cou += (file->str[pos] == ',' && c[0] == 1 && !c[1] && !c[2] && !c[3]);
		c[0] += (file->str[pos] == '[') - (file->str[pos] == ']');
		c[1] += (file->str[pos] == '{') - (file->str[pos] == '}');
		if (file->str[pos] == '\"' && file->str[pos - 1] != '\\')
			c[2] ^= 1;
		if (file->str[pos] == '\'' && file->str[pos - 1] != '\\')
			c[3] ^= 1;
		pos++;
	}
	return (cou);
}

t_json_value	*new_array(t_json_file *f, t_json_value *parent)
{
	t_json_array	*arr;
	t_json_value	*ret;
	unsigned long	index;

	if (f->str == NULL || f->pos >= f->len
	|| f->str[f->pos] != '['
		|| (ret = ft_fill_json_value(parent, array, NULL)) == NULL)
		return (NULL);
	if ((arr = (t_json_array *)malloc(sizeof(t_json_array))) == NULL)
		return (ft_free(ret));
	arr->nb = get_array_size(f, f->pos + 1);
	if ((arr->value = (t_json_value **)malloc(sizeof(t_json_value *)
	* arr->nb)) == NULL && ft_free(ret) == NULL)
		return (NULL);
	index = 0;
	while (index < arr->nb)
	{
		if ((arr->value[index++] = new_json_value(f, ret)) == NULL)
		{
			json_free(ret);
			json_free_array(arr);
			return(NULL);
		}
		if (f->str[f->pos] == ':' && f->pos < f->len)
		{
			json_free(ret);
			json_free_array(arr);
			return (NULL);
		}
		
		pass_spaces(f);
		f->pos += (f->str[f->pos] == ',' && f->pos < f->len) ? 1 : 0;
	}
	pass_spaces(f);
	f->pos += (f->str[f->pos] == ']' && f->pos < f->len) ? 1 : 0;
	ret->ptr = (void *)arr;
	return (ret);
}
