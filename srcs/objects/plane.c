/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:42:16 by alacrois          #+#    #+#             */
/*   Updated: 2018/08/26 18:08:39 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <global.h>

bool			plane_collision(t_ray ray, t_plane *pl, \
								t_rpoint pos, t_rpoint *p)
{
	t_rpoint	vpl;
	t_rpoint	c;
	double		tmp;
	double		solution;

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
