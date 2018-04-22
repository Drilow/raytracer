/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 21:10:11 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/02 21:10:18 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_bool	get_camera(t_rtv1 *r, char *s, t_rpoint *angle)
{
	int			index;

	index = 0;
	if (get_next_nb(s, &index, &(r->cam_position.x), NULL) == false || \
		get_next_nb(s, &index, &(r->cam_position.y), NULL) == false || \
		get_next_nb(s, &index, &(r->cam_position.z), NULL) == false || \
		get_next_nb(s, &index, &(angle->x), NULL) == false || \
		get_next_nb(s, &index, &(angle->y), NULL) == false || \
		get_next_nb(s, &index, &(angle->z), NULL) == false)
		return (false);
	return (true);
}

t_bool			set_camera(t_rtv1 *r, char *s)
{
	t_rpoint	angle;
	t_point		p;

	if (get_camera(r, s, &angle) == false)
		return (false);
	angle.x = ((double)((int)angle.x % 360) / 360) * (2 * PI);
	angle.y = ((double)((int)angle.y % 360) / 360) * (2 * PI);
	angle.z = ((double)((int)angle.z % 360) / 360) * (2 * PI);
	p.y = -1;
	while (++p.y < WIN_SIZE_Y)
	{
		p.x = -1;
		while (++p.x < WIN_SIZE_X)
		{
			r->rays[p.y][p.x].p = r->cam_position;
			rotate(&(r->rays[p.y][p.x].vector), angle);
		}
	}
	return (true);
}

t_bool			find_collisions(t_rpoint factors, t_dpoint *solutions)
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

void			usage(char *s)
{
	ft_putendl(s);
	ft_exit("usage : ./rtv1 [scene]");
}
