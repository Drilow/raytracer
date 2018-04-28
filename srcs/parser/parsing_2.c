/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:04:46 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 17:17:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <extra/extra_defs.h>

t_bool			get_next_nb(char *s, int *index, double *nb1, \
							unsigned char *nb2)
{
	int			i;

	i = *index;
	while (ft_isdigit(s[i]) == 0 && s[i] != '-' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (false);
	if (nb1 != NULL)
		*nb1 = (double)ft_atoi(s + i);
	else
		*nb2 = (unsigned char)ft_atoi(s + i);
	while (ft_isdigit(s[i]) == 1 || s[i] == '-')
		i++;
	*index = i;
	return (true);
}

t_bool			get_next_rpoint(char *s, t_rpoint *p, int *index)
{
	if (get_next_nb(s, index, &(p->x), NULL) == true && \
		get_next_nb(s, index, &(p->y), NULL) == true && \
		get_next_nb(s, index, &(p->z), NULL) == true)
		return (true);
	return (false);
}

static int		transform(char *s, t_rpoint *p, int *index)
{
	t_rpoint	tmp;
	int			i;

	i = *index;
	while (s[i] != 'r' && s[i] != 't' && s[i] != '\0')
		i++;
	if (cmp_chars(s, "rotate", i) == true)
	{
		if (get_next_rpoint(s, &tmp, index) == true)
		{
			p->x = ((double)((int)tmp.x % 360) / 360) * (2 * PI);
			p->y = ((double)((int)tmp.y % 360) / 360) * (2 * PI);
			p->z = ((double)((int)tmp.z % 360) / 360) * (2 * PI);
			return (1);
		}
		return (0);
	}
	if (cmp_chars(s, "translate", i) == true \
		&& get_next_rpoint(s, p, index) == true)
		return (2);
	*index = i;
	return (0);
}

static t_bool	get_obj_core(char *s, t_obj *obj, int *index, t_rgb *clr)
{
	t_rgb		*color;

	color = clr;
	if (obj != NULL)
	{
		color = &(obj->color);
		if (obj->type == 1 && \
			get_sphere(s, (t_sphere *)obj->obj, index) == false)
			return (false);
		if (obj->type == 2 && \
			get_plane(s, (t_plane *)obj->obj, index) == false)
			return (false);
		if (obj->type == 3 && \
			get_cone(s, (t_cone *)obj->obj, index) == false)
			return (false);
		if (obj->type == 4 && \
			get_cylinder(s, (t_cylinder *)obj->obj, index) == false)
			return (false);
	}
	if (get_next_nb(s, index, NULL, &(color->r)) == false || \
		get_next_nb(s, index, NULL, &(color->g)) == false || \
		get_next_nb(s, index, NULL, &(color->b)) == false || \
		get_next_nb(s, index, NULL, &(color->trans)) == false)
		return (false);
	return (true);
}

t_bool			get_obj(char *s, void *o, int *index, int type)
{
	t_rpoint	*t;
	int			result;
	t_obj		*obj;
	t_rgb		*color;

	obj = NULL;
	color = NULL;
	if (type == 0 && get_light(s, (t_light *)o, index) == false)
		return (false);
	else if (type != 0)
		obj = (t_obj *)o;
	else
		color = &(((t_light *)o)->color);
	if (get_obj_core(s, obj, index, color) == false)
		return (false);
	t = (t_rpoint *)ft_malloc(sizeof(t_rpoint));
	while ((result = transform(s, t, index)) != 0)
	{
		if (result == 1)
			rotate_obj(o, type, *t);
		else
			translate_obj(o, type, *t);
	}
	return (true);
}
