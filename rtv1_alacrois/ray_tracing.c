/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:11:40 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/02 21:00:45 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_bool				collision(t_ray ray, t_obj *o, t_rpoint *p)
{
	if (o->type == 1 && sphere_collision(ray, (t_sphere *)o->obj, p) == true)
		return (true);
	else if (o->type == 2 && \
			plane_collision(ray, (t_plane *)o->obj, p) == true)
		return (true);
	else if (o->type == 3 && \
			cone_collision(ray, (t_cone *)o->obj, p) == true)
		return (true);
	else if (o->type == 4 && \
			cylinder_collision(ray, (t_cylinder *)o->obj, p) == true)
		return (true);
	return (false);
}

t_collision			ray_tracing(t_rtv1 *r, t_ray ray)
{
	t_collision		c;
	t_rpoint		p;
	t_obj			*tmp;
	int				i;

	c.o = NULL;
	tmp = r->objects;
	i = 0;
	while (tmp != NULL)
	{
		if (collision(ray, tmp, &p) == true)
		{
			if (c.o == NULL || (deltasq(ray.p, p) < deltasq(ray.p, c.p)))
			{
				c.p = p;
				c.o = tmp;
			}
		}
		i++;
		tmp = tmp->next;
	}
	return (c);
}
