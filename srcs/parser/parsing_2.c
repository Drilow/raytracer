/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:04:46 by alacrois          #+#    #+#             */
/*   Updated: 2018/08/19 16:46:00 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <extra/extra_defs.h>
#include <parser/parser.h>
#include <libft.h>
#include <geometry/geometry.h>
#include <objects/object.h>
#include <maths/transformations.h>

bool			get_next_nb(char *s, int *index, double *nb1, \
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

bool			get_next_rpoint(char *s, t_rpoint *p, int *index)
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

bool			get_obj(char *s, void *o, int *index, int type)
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
	t = (t_rpoint *)malloc(sizeof(t_rpoint));
	while ((result = transform(s, t, index)) != 0)
	{
		if (result == 1)
			rotate_obj(o, type, *t);
		else
			translate_obj(o, type, *t);
	}
	return (true);
}
