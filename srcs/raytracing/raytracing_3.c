/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 16:51:25 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/26 19:46:58 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>

extern t_global			g_global;

static void			init_add_collision(t_collision **tmp, t_collision **new, \
										t_collision *c, t_collision *tmpc)
{
	*tmp = c;
	if (!(*new = (t_collision *)malloc(sizeof(t_collision))))
	{
		free_collisions(c);
		ft_exit("Malloc error ('raytracing_3.c' --> Ln 22)", 1);
	}
	**new = *tmpc;
	(*new)->next = NULL;
	(*new)->reflected = NULL;
}

t_collision			*add_collision(t_ray ray, t_collision *c, t_collision *tmpc)
{
	t_collision		*tmp;
	t_collision		*new;

	init_add_collision(&tmp, &new, c, tmpc);
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

void				reflexion(t_rt *r, t_ray ray, t_collision *c, int index)
{
	t_collision		*tmp;
	t_ray			reflected_ray;

	tmp = c;
	while (tmp != NULL)
	{
		if (tmp->o != NULL && tmp->o->reflex > 0)
		{
			reflected_ray.p = tmp->p;
			reflected_ray.vector = reflected_vector(ray.vector, tmp->normal);
			if (vlength(reflected_ray.vector) > 0)
				tmp->reflected = ray_tracing(r, reflected_ray, index - 1);
		}
		tmp = tmp->next;
	}
}
