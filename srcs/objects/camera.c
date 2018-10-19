/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:38:43 by adleau            #+#    #+#             */
/*   Updated: 2018/10/17 18:06:24 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <objects/object.h>
#include <parser/parser.h>
#include <maths/transformations.h>

#include <libft.h>

extern t_global g_global;

static bool	get_camera(char *s, t_rpoint *angle)
{
	int			index;

	index = 0;
	if (get_next_nb(s, &index, &(g_global.r->cam_position.x), NULL) == false || \
		get_next_nb(s, &index, &(g_global.r->cam_position.y), NULL) == false || \
		get_next_nb(s, &index, &(g_global.r->cam_position.z), NULL) == false || \
		get_next_nb(s, &index, &(angle->x), NULL) == false || \
		get_next_nb(s, &index, &(angle->y), NULL) == false || \
		get_next_nb(s, &index, &(angle->z), NULL) == false)
		return (false);
	return (true);
}

bool			set_camera(char *s)
{
	t_rpoint	angle;
	t_point		p;

	if (get_camera(s, &angle) == false)
		return (false);
	angle.x = ((double)((int)angle.x % 360) / 360) * (2 * PI);
	angle.y = ((double)((int)angle.y % 360) / 360) * (2 * PI);
	angle.z = ((double)((int)angle.z % 360) / 360) * (2 * PI);
	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			g_global.r->rays[p.y][p.x].p = g_global.r->cam_position;
			rotate(&(g_global.r->rays[p.y][p.x].vector), angle);
		}
	}
	return (true);
}

bool			find_collisions(t_rpoint factors, t_dpoint *solutions)
{
	if (ft_solve_equation(factors, solutions) == false)
		return (false);
	if (solutions->x < 0)
	{
		if (solutions->y < 0)
			return (false);
		solutions->x = solutions->y;
	}
	else if (solutions->y < 0)
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
