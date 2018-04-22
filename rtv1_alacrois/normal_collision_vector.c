/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_collision_vector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:37:03 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/27 17:29:17 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_rpoint		get_cone_ncv(t_cone *c, t_rpoint p)
{
	t_rpoint		ncv;
	double			d;
	t_rpoint		v1;
	t_rpoint		v2;
	double			vlen;

	if (vangle(c->vector, get_vector(c->summit, p)) < (c->angle * 0.999999))
		return (c->vector);
	d = point_to_line_distance(p, c->summit, c->vector);
	vlen = (d / tan(c->angle)) + (d / tan((PI / 2) - c->angle));
	v1 = get_vector(c->summit, p);
	v2 = vnorm_to_length(c->vector, vlen);
	ncv = set_rpoint(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	if (vangle(c->vector, get_vector(c->summit, p)) > (c->angle * 1.0000001))
		ncv = set_rpoint(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return (ncv);
}

static t_rpoint		get_cylinder_ncv(t_cylinder *cy, t_rpoint p)
{
	t_rpoint		ncv;
	double			d1;
	double			d2;
	t_rpoint		c;
	t_rpoint		v;

	if (point_to_line_distance(p, cy->summit, cy->vector) \
		< (cy->radius * 0.9999999))
		return (cy->vector);
	d1 = deltasq(cy->summit, p);
	d2 = sqrt(d1 - pow(cy->radius, 2));
	v = vnorm_to_length(cy->vector, d2);
	c = new_point(cy->summit, v, 1);
	if (deltasq(c, p) > d1)
		c = new_point(cy->summit, v, -1);
	ncv = get_vector(c, p);
	return (ncv);
}

t_rpoint			normal_collision_vector(t_obj *o, t_rpoint p)
{
	t_rpoint			ncv;

	if (o->type == 1)
		ncv = get_vector(((t_sphere *)o->obj)->center, p);
	if (o->type == 2)
		ncv = ((t_plane *)o->obj)->vector;
	if (o->type == 3)
		ncv = get_cone_ncv((t_cone *)o->obj, p);
	if (o->type == 4)
		ncv = get_cylinder_ncv((t_cylinder *)o->obj, p);
	return (ncv);
}
