/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:38:43 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 15:41:18 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <maths/transformations.h>

extern t_global g_global;

bool			set_camera(t_rpoint angle)
{
	t_point		p;

	angle.x = ((double)((int)angle.x % 360) / 360) * (2 * PI);
	angle.y = ((double)((int)angle.y % 360) / 360) * (2 * PI);
	angle.z = ((double)((int)angle.z % 360) / 360) * (2 * PI);
	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			g_global.r.rays[p.y][p.x].p = g_global.r.cam_position;
			rotate(&(g_global.r.rays[p.y][p.x].vector), angle);
		}
	}
	return (true);
}

bool			find_collisions(t_rpoint factors, \
								t_dpoint *solutions, double minimum)
{
	if (ft_solve_equation(factors, solutions) == false)
		return (false);
	if (solutions->x < minimum)
	{
		if (solutions->y < minimum)
			return (false);
		solutions->x = solutions->y;
	}
	else if (solutions->y < minimum)
		solutions->y = solutions->x;
	return (true);
}

t_ray			get_ray(t_rpoint p, t_rpoint vector)
{
	t_ray			ray;

	ray.p = p;
	ray.vector = vector;
	return (ray);
}
