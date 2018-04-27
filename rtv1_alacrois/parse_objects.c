/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:38:19 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/27 19:17:17 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bool			get_sphere(char *s, t_sphere *sph, int *index)
{
	if (get_next_nb(s, index, &(sph->center.x), NULL) == false || \
		get_next_nb(s, index, &(sph->center.y), NULL) == false || \
		get_next_nb(s, index, &(sph->center.z), NULL) == false || \
		get_next_nb(s, index, &(sph->radius), NULL) == false)
		return (false);
	return (true);
}

t_bool			get_plane(char *s, t_plane *pl, int *index)
{
	if (get_next_nb(s, index, &(pl->vector.x), NULL) == false || \
		get_next_nb(s, index, &(pl->vector.y), NULL) == false || \
		get_next_nb(s, index, &(pl->vector.z), NULL) == false || \
		get_next_nb(s, index, &(pl->p.x), NULL) == false || \
		get_next_nb(s, index, &(pl->p.y), NULL) == false || \
		get_next_nb(s, index, &(pl->p.z), NULL) == false)
		return (false);
	return (true);
}

t_bool			get_cone(char *s, t_cone *c, int *index)
{
	double		angle;
	int			i;

	if (get_next_nb(s, index, &(c->summit.x), NULL) == false || \
		get_next_nb(s, index, &(c->summit.y), NULL) == false || \
		get_next_nb(s, index, &(c->summit.z), NULL) == false || \
		get_next_nb(s, index, &(c->vector.x), NULL) == false || \
		get_next_nb(s, index, &(c->vector.y), NULL) == false || \
		get_next_nb(s, index, &(c->vector.z), NULL) == false || \
		get_next_nb(s, index, &angle, NULL) == false)
		return (false);
	c->angle = (angle / 360) * (2 * PI);
	i = *index;
	while (s[i] != 'I' && s[i] != '\0')
		i++;
	c->infinite = cmp_chars(s, "INF", i);
	return (true);
}

t_bool			get_cylinder(char *s, t_cylinder *c, int *index)
{
	int			i;

	if (get_next_nb(s, index, &(c->summit.x), NULL) == false || \
		get_next_nb(s, index, &(c->summit.y), NULL) == false || \
		get_next_nb(s, index, &(c->summit.z), NULL) == false || \
		get_next_nb(s, index, &(c->vector.x), NULL) == false || \
		get_next_nb(s, index, &(c->vector.y), NULL) == false || \
		get_next_nb(s, index, &(c->vector.z), NULL) == false || \
		get_next_nb(s, index, &(c->radius), NULL) == false)
		return (false);
	i = *index;
	while (s[i] != 'I' && s[i] != '\0')
		i++;
	c->infinite = cmp_chars(s, "INF", i);
	return (true);
}

t_bool			get_light(char *s, t_light *l, int *index)
{
	if (get_next_nb(s, index, &(l->source.x), NULL) == false || \
		get_next_nb(s, index, &(l->source.y), NULL) == false || \
		get_next_nb(s, index, &(l->source.z), NULL) == false)
		return (false);
	return (true);
}
