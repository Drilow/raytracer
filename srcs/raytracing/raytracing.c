/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:11:40 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/17 22:37:21 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>
#define GTKMGR g_global.gtk_mgr

extern t_global			g_global;

void					free_collisions(t_collision *c)
{
	t_collision			*tmp;
	t_collision			*tmp_next;

	tmp = c;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		free(tmp);
		tmp = tmp_next;
	}
}

//t_bool				collision(t_ray ray, t_obj *o, t_rpoint *p)
bool					collision(t_ray ray, t_collision *c)
{
	t_obj				*o;
	t_rpoint			*p;

	o = c->o;
	p = &(c->p);

	if (o->enabled == false)
		return (false);
	if (o->type == 1 && sphere_collision(ray, o, p) == true)
		return (true);
	else if (o->type == 2 && \
//			plane_collision(ray, (t_plane *)o->obj, p) == true)
			 plane_collision(ray, (t_plane *)o->obj, o->position, p) == true)
		return (true);
	else if (o->type == 3 && \
//			cone_collision(ray, (t_cone *)o->obj, p) == true)
			 cone_collision(ray, o, p) == true)
		return (true);
	else if (o->type == 4 && \
//			cylinder_collision(ray, (t_cylinder *)o->obj, p) == true)
			 cylinder_collision(ray, o, p) == true)
		return (true);
	else if ((o->type == 6 || (o->type / 10) == 6) && \
			 poly_obj_collision(ray, (t_poly_obj *)o->obj, c) == true)
        return (true);
	return (false);
}

static t_collision	*add_collision(t_ray ray, t_collision *c, t_collision *tmpc)
{
    t_collision		*tmp;
    t_collision		*new;

	tmp = c;
	new = (t_collision *)malloc(sizeof(t_collision));
	*new = *tmpc;
	new->next = NULL;
	if (deltasq(ray.p, tmpc->p) < deltasq(ray.p, c->p))
	{
		new->next = c;
		return (new);
	}
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			tmp->next = new;
		else if (deltasq(ray.p, tmpc->p) < deltasq(ray.p, tmp->next->p))
		{
			new->next = tmp->next;
			tmp->next = new;
			return (c);
		}
		tmp = tmp->next;
	}
	return (c);
}

t_collision			*ray_tracing(t_rt *r, t_ray ray)
{
	t_collision		*c;
	t_rpoint		p;
	t_collision		tmpc;
	t_obj			*tmp;
	int				i;

	if (!(c = (t_collision *)malloc(sizeof(t_collision))))
		exit(1);
	c->next = NULL;
	c->reflected = NULL;
	c->o = NULL;
	tmp = r->objects;
	i = 0;
	p = set_rpoint(0, 0, 0);
	while (tmp != NULL)
	{
//		if (collision(ray, tmp, &p) == true)
		tmpc.o = tmp;
		tmpc.p = p;
		if (collision(ray, &tmpc) == true)
		{
//			if (c.o == NULL || (deltasq(ray.p, tmpc.p) < deltasq(ray.p, c.p)))
			if (c->o == NULL)
			{
				c->p = tmpc.p;
				c->o = tmp;
				c->normal = tmpc.normal;
			}
			else
                c = add_collision(ray, c, &tmpc);
		}
		i++;
		tmp = tmp->next;
	}
	return (c);
}
