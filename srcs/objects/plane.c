/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:42:16 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 19:53:09 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <stdbool.h>

bool			plane_collision(t_ray ray, t_plane *pl, t_rpoint *p)
{
	t_rpoint	vpl;
	t_rpoint	c;
	t_rpoint	ppl;
	double		tmp;
	double		solution;

	vpl = pl->vector;
	c = ray.p;
	ppl = pl->p;
	tmp = scalar(ray.vector, pl->vector);
	if (tmp == 0)
		return (false);
	solution = (scalar(vpl, ppl) - scalar(vpl, c)) / tmp;
	if (solution <= 0)
		return (false);
	*p = new_point(c, ray.vector, solution);
	return (true);
}
