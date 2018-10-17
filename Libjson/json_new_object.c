/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_new_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:31:34 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/17 13:36:21 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "includes/json.h"

void			json_set_pair(t_json_pair **pair, unsigned long nb)
{
	unsigned long nbb;

	nbb = 0;
	while (nbb < nb)
		pair[nbb++] = NULL;
}

unsigned long	get_size(t_json_file *file, unsigned long pos)
{
	unsigned long cou;
	unsigned long count2;
	unsigned long *c;

	c = (unsigned long[4]){(file->str[file->pos++] == '{'), 0, 0, 0};
	while (pos < file->len && ft_isspace(file->str[pos]))
		pos++;
	cou = 1;
	count2 = 0;
	if (file->str[pos] == '}')
		return (0);
	while (pos < file->len && c[0])
	{
		cou += (file->str[pos] == ',' && c[0] == 1 && !c[1] && !c[2] && !c[3]);
		count2 += (file->str[pos] == ':' && c[0] == 1 && !c[1]
		&& !c[2] && !c[3]);
		c[0] += (file->str[pos] == '{') - (file->str[pos] == '}');
		c[1] += (file->str[pos] == '[') - (file->str[pos] == ']');
		if (file->str[pos] == '\"' && file->str[pos - 1] != '\\')
			c[2] ^= 1;
		if (file->str[pos] == '\'' && file->str[pos - 1] != '\\')
			c[3] ^= 1;
		pos++;
	}
	return ((cou == count2) ? cou : (unsigned long)-1);
}

t_json_pair		*new_pair(t_json_file *f, t_json_value *parent)
{
	t_json_pair *pair;

	if (f->str[f->pos] == ':')
		return (NULL);
	pass_spaces(f);
	if ((pair = (t_json_pair *)malloc(sizeof(t_json_pair))) == NULL)
		return (pair);
	ft_bzero(pair, sizeof(t_json_pair));
	if (f->str[f->pos] != '"')
		return (ft_free(pair));
	if ((pair->key = make_new_string(f)) == NULL
	&& ft_free(pair->key->str) == NULL)
		return (ft_free(pair));
	pass_spaces(f);
	if (f->str[f->pos] != ':' && ft_free(pair->key) == NULL)
		return (ft_free(pair));
	f->pos++;
	pass_spaces(f);
	if ((pair->value = new_json_value(f, parent)) == NULL)
	{
		json_free_pair(pair);
		return (NULL);
	}
	return (pair);
}

t_json_object	*ft_set_obj(t_json_file *f, t_json_object *obj)
{
	if ((obj = (t_json_object *)malloc(sizeof(t_json_object))) == NULL)
		return (NULL);
	if ((obj->nb = get_size(f, f->pos + 1)) == 0)
		return (ft_free(obj));
	if (obj->nb == (unsigned long)-1)
		return (ft_free(obj));
	if ((obj->pair = (t_json_pair **)malloc(sizeof(t_json_pair *)
	* obj->nb)) == NULL)
		return (ft_free(obj));
	return (obj);
}

t_json_value	*new_object(t_json_file *f, t_json_value *parent,
unsigned long index)
{
	t_json_object	*obj;
	t_json_value	*ret;

	obj = 0;
	if (f->pos >= f->len || f->str == NULL || f->str[f->pos] != '{'
	|| (ret = ft_fill_json_value(parent, object, NULL)) == NULL)
		return (NULL);
	if ((obj = ft_set_obj(f, obj)) == NULL)
		return (ft_free(ret));
	json_set_pair(obj->pair, obj->nb);
	while (index < obj->nb)
	{
		if ((obj->pair[index++] = new_pair(f, ret)) == NULL)
			return (ft_exit_object(ret, obj));
		pass_spaces(f);
		f->pos += (f->str[f->pos] == ',' && f->pos < f->len) ? 1 : 0;
	}
	pass_spaces(f);
	if (f->str[f->pos] != '}')
		return (ft_exit_object(ret, obj));
	f->pos += (f->str[f->pos] == '}' && f->pos < f->len) ? 1 : 0;
	ret->ptr = (void*)obj;
	return (ret);
}
