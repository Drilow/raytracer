/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:11:40 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/29 17:50:31 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>

extern t_global			g_global;

static bool			init_ray_tracing(t_rt *r, int r_index, \
										t_collision **c, t_obj **tmp)
{
	if (!(*c = (t_collision *)malloc(sizeof(t_collision))))
		ft_exit("Malloc error ('raytracing_1.c' --> Ln 21)", 1);
	if (r_index < 0)
	{
		free(*c);
		return (false);
	}
	(*c)->next = NULL;
	(*c)->reflected = NULL;
	(*c)->o = NULL;
	*tmp = r->objects;
	return (true);
}

static void			ray_tracing_core(t_obj *tmp, t_collision **c, t_ray ray)
{
	t_collision		tmpc;
	t_rpoint		p;

	p = set_rpoint(0, 0, 0);
	while (tmp != NULL)
	{
		tmpc.o = tmp;
		tmpc.p = p;
		if (collision(ray, &tmpc) == true)
		{
			if ((*c)->o == NULL)
			{
				(*c)->p = tmpc.p;
				(*c)->o = tmp;
				(*c)->normal = tmpc.normal;
			}
			else
				(*c) = add_collision(ray, *c, &tmpc);
		}
		tmp = tmp->next;
	}
}

t_collision			*ray_tracing(t_rt *r, t_ray ray, int r_index)
{
	t_collision		*c;
	t_obj			*tmp;

	if (init_ray_tracing(r, r_index, &c, &tmp) == false)
		return (NULL);
	ray_tracing_core(tmp, &c, ray);
	if (c->o != NULL)
	{
		clean_collision_list(c);
		reflexion(r, ray, c, r_index);
	}
	else
	{
		free(c);
		return (NULL);
	}
	return (c);
}
