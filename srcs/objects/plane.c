/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:42:16 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/05 15:43:06 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

bool			plane_collision(t_ray ray, t_plane *pl, \
								t_rpoint pos, t_rpoint *p)
{
	t_rpoint	vpl;
	t_rpoint	c;
	double		tmp;
	double		solution;

	tmp = 0;
	vpl = pl->vector;
	c = ray.p;
	tmp = scalar(ray.vector, vpl);
	if (tmp == 0)
		return (false);
	solution = (scalar(vpl, pos) - scalar(vpl, c)) / tmp;
	if (solution < MIN_DISTANCE)
		return (false);
	*p = new_point(c, ray.vector, solution);
	return (true);
}
