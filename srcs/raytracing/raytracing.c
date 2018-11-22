/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:11:40 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/22 20:23:41 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>
#define GTKMGR g_global.gtk_mgr

extern t_global			g_global;

//t_bool				collision(t_ray ray, t_obj *o, t_rpoint *p)
bool					collision(t_ray ray, t_collision *c,  bool test)
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
			 poly_obj_collision(ray, (t_poly_obj *)o->obj, c, test) == true)
        return (true);
	return (false);
}

t_collision			ray_tracing(t_rt *r, t_ray ray, bool test)
{
	t_collision		c;
	t_rpoint		p;
	t_collision		tmpc;
	t_obj			*tmp;
	int				i;

	c.o = NULL;
	tmp = r->objects;
	i = 0;
	p = set_rpoint(0, 0, 0);
	while (tmp != NULL)
	{
//		if (collision(ray, tmp, &p) == true)
		tmpc.o = tmp;
		tmpc.p = p;
		if (collision(ray, &tmpc, test) == true)
		{
			if (c.o == NULL || (deltasq(ray.p, tmpc.p) < deltasq(ray.p, c.p)))
			{
				c.p = tmpc.p;
				c.o = tmp;
				c.normal = tmpc.normal;
			}
		}
		i++;
		tmp = tmp->next;
	}
	return (c);
}
