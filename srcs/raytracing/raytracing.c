/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:11:40 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/30 17:33:28 by alacrois         ###   ########.fr       */
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
		if (tmp->reflected != NULL)
			free_collisions(tmp->reflected);
		free(tmp);
		tmp = tmp_next;
	}
}

/*
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
*/

bool					collision(t_ray ray, t_collision *c)
{
	t_obj				*o;
	t_rpoint			*p;

	o = c->o;
	p = &(c->p);

	if (o->enabled == false)
		return (false);
	if (o->type == 1 && sphere_collision(ray, o, p) == false)
		return (false);
	else if (o->type == 2 && \
			 plane_collision(ray, (t_plane *)o->obj, o->position, p) == false)
		return (false);
	else if (o->type == 3 && \
			 cone_collision(ray, o, p) == false)
		return (false);
	else if (o->type == 4 && \
			 cylinder_collision(ray, o, p) == false)
		return (false);
	else if ((o->type == 6 || (o->type / 10) == 6) && \
			 poly_obj_collision(ray, (t_poly_obj *)o->obj, c) == false)
        return (false);
	else if (o->type < 1)
		return (false);
	c->normal = normal_collision_vector(*c);
	return (true);
}

static t_collision	*add_collision(t_ray ray, t_collision *c, t_collision *tmpc)
{
    t_collision		*tmp;
    t_collision		*new;

	tmp = c;
	new = (t_collision *)malloc(sizeof(t_collision));
	*new = *tmpc;
	new->next = NULL;
	new->reflected = NULL;
	if (deltasq(ray.p, tmpc->p) < deltasq(ray.p, c->p))
	{
		new->next = c;
		return (new);
	}
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			tmp->next = new;
			return (c);
		}
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

static void			clean_collision_list(t_collision *c)
{
	t_collision		*tmp;

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


static t_rpoint		reflected_vector(t_rpoint v, t_rpoint normal)
{
	t_rpoint		rv;
	t_rpoint		tmp;
	double			sc;

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

static void			reflexion(t_rt *r, t_ray ray, t_collision *c, int index)
{
	t_collision		*tmp;
	t_ray			reflected_ray;

	tmp = c;
	//printf("debug 1\n");
	while (tmp != NULL)
	{
		// a remplacer par if (tmp->o->reflexion > 0) :
		//printf("debug 2\n");
		if (tmp->o != NULL && tmp->o->color.trans > 0)
		{
		//	printf("debug 3\n");
			reflected_ray.p = tmp->p;
			reflected_ray.vector = reflected_vector(ray.vector, c->normal);
		//	printf("debug 4\n");
			if (vlength(reflected_ray.vector) > 0)
				tmp->reflected = ray_tracing(r, reflected_ray, index - 1);
		//	printf("debug 5\n");
		}
		//printf("debug 6\n");
		tmp = tmp->next;
	}
	//printf("debug 7\n");
}

t_collision			*ray_tracing(t_rt *r, t_ray ray, int r_index)
{
	t_collision		*c;
	t_rpoint		p;
	t_collision		tmpc;
	t_obj			*tmp;
	int				i;

//	printf("d0\n");
	//printf("debug rt1\n");
	if (!(c = (t_collision *)malloc(sizeof(t_collision))))
		exit(1);
	if (r_index < 0)
		return (NULL);
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
//	printf("d1\n");
	//printf("debug rt2\n");
	if (c->o != NULL)
	{
		clean_collision_list(c);
//		printf("d2\n");
		reflexion(r, ray, c, r_index);
	}
	else
	{
		free(c);
		return (NULL);
	}
//	printf("d3\n");
	//printf("debug rt3\n");
	return (c);
}
