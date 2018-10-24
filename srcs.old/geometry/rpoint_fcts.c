/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpoint_fcts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:43:04 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 20:08:29 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry/geometry.h>

t_rpoint		set_rpoint(double x, double y, double z)
{
	t_rpoint		p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_rpoint		new_point(t_rpoint start, t_rpoint vector, double factor)
{
	t_rpoint		a;

	a.x = start.x + (vector.x * factor);
	a.y = start.y + (vector.y * factor);
	a.z = start.z + (vector.z * factor);
	return (a);
}

t_rpoint		closer(t_rpoint p, t_rpoint a, t_rpoint b)
{
	if (deltasq(p, a) <= deltasq(p, b))
		return (a);
	return (b);
}

double			deltasq(t_rpoint a, t_rpoint b)
{
	t_rpoint	d;

	d.x = (a.x - b.x) * (a.x - b.x);
	d.y = (a.y - b.y) * (a.y - b.y);
	d.z = (a.z - b.z) * (a.z - b.z);
	return (d.x + d.y + d.z);
}

double			point_to_line_distance(t_rpoint p, t_rpoint line_p, \
				t_rpoint line_v)
{
	double		d;
	t_rpoint	cp;

	cp = cross_product(get_vector(line_p, p), line_v);
	d = vlength(cp) / vlength(line_v);
	return (d);
}
