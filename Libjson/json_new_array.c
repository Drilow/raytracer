/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 15:50:36 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/17 13:35:39 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/json.h"
#include "../libft/libft.h"

void			json_set_val(t_json_value **val, unsigned long nb)
{
	unsigned long nbb;

	nbb = 0;
	while (nbb < nb)
		val[nbb++] = NULL;
}

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

t_json_array	*ft_set_arr(t_json_file *f, t_json_array *arr)
{
	if ((arr = (t_json_array *)malloc(sizeof(t_json_array))) == NULL)
		return (NULL);
	if ((arr->nb = get_array_size(f, f->pos + 1)) == 0)
		return (ft_free(arr));
	if ((arr->value = (t_json_value **)malloc(sizeof(t_json_value *)
	* arr->nb)) == NULL)
		return (ft_free(arr));
	return (arr);
}

t_json_value	*new_array(t_json_file *f, t_json_value *parent,
unsigned long index)
{
	t_json_array	*arr;
	t_json_value	*ret;

	arr = 0;
	if (f->str == NULL || f->pos >= f->len
	|| f->str[f->pos] != '['
		|| (ret = ft_fill_json_value(parent, array, NULL)) == NULL)
		return (NULL);
	if ((arr = ft_set_arr(f, arr)) == NULL)
		return (ft_free(ret));
	json_set_val(arr->value, arr->nb);
	while (index < arr->nb)
	{
		if ((arr->value[index++] = new_json_value(f, ret)) == NULL)
			return (ft_exit_array(ret, arr));
		pass_spaces(f);
		f->pos += (f->str[f->pos] == ',' && f->pos < f->len) ? 1 : 0;
	}
	pass_spaces(f);
	if (f->str[f->pos] != ']')
		return (ft_exit_array(ret, arr));
	f->pos += (f->str[f->pos] == ']' && f->pos < f->len) ? 1 : 0;
	ret->ptr = (void *)arr;
	return (ret);
}
