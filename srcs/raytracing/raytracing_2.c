/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:04:36 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/29 03:29:01 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>

extern t_global			g_global;

void					free_collisions(t_collision *c)
{
	t_collision			*tmp;
	t_collision			*tmp_next;

	tmp = c;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		if (tmp->reflected != NULL)
			free_collisions(tmp->reflected);
		free(tmp);
		tmp = tmp_next;
	}
}

static void				collision_normal(t_ray ray, t_obj *o, t_collision *c)
{
	c->normal = normal_collision_vector(*c);
	if ((o->type == 6 || (o->type / 10) == 6 || o->type == 2) && \
		(vangle(ray.vector, c->normal) > (PI / 2) || \
		vangle(ray.vector, c->normal) < (-PI / 2)))
		c->normal = set_rpoint(-c->normal.x, -c->normal.y, -c->normal.z);
}

bool					collision(t_ray ray, t_collision *c)
{
	t_obj				*o;

	o = c->o;
	if (o->enabled == false)
		return (false);
	if (o->type == 1 && sphere_collision(ray, o, &(c->p)) == false)
		return (false);
	else if (o->type == 2 && \
		plane_collision(ray, (t_plane *)o->obj, o->position, &(c->p)) == false)
		return (false);
	else if (o->type == 3 && \
		cone_collision(ray, o, &(c->p)) == false)
		return (false);
	else if (o->type == 4 && \
		cylinder_collision(ray, o, &(c->p)) == false)
		return (false);
	else if ((o->type == 6 || (o->type / 10) == 6) && \
		poly_obj_collision(ray, (t_poly_obj *)o->obj, c) == false)
		return (false);
	else if (o->type < 1)
		return (false);
	collision_normal(ray, o, c);
	return (true);
}

void					clean_collision_list(t_collision *c)
{
	t_collision			*tmp;

	tmp = c;
	while (tmp != NULL)
	{
		if (tmp->o != NULL && tmp->o->color.trans == 0)
		{
			if (tmp->next != NULL)
				free_collisions(tmp->next);
			tmp->next = NULL;
			tmp = NULL;
		}
		else
			tmp = tmp->next;
	}
}

t_rpoint				reflected_vector(t_rpoint v, t_rpoint normal)
{
	t_rpoint			rv;
	t_rpoint			tmp;
	double				sc;

	normal = vnorm(normal);
	sc = scalar(normal, v);
	tmp.x = normal.x * 2 * sc;
	tmp.y = normal.y * 2 * sc;
	tmp.z = normal.z * 2 * sc;
	rv.x = v.x - tmp.x;
	rv.y = v.y - tmp.y;
	rv.z = v.z - tmp.z;
	return (rv);
}
