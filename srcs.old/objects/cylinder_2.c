/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collision_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:35:16 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 20:06:52 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry/geometry.h>
#include <objects/object.h>

static t_dpoint	get_const1(t_ray ray, t_cylinder *cy)
{
	t_dpoint		c1;
	t_rpoint		vc;
	t_rpoint		vr;
	t_rpoint		c;
	t_rpoint		s;

	vc = cy->vector;
	vr = ray.vector;
	c = ray.p;
	s = cy->summit;
	c1.x = (vr.y * vc.z) - (vr.z * vc.y);
	c1.y = (c.y * vc.z) + (s.z * vc.y) - (s.y * vc.z) - (c.z * vc.y);
	return (c1);
}

static t_dpoint	get_const2(t_ray ray, t_cylinder *cy)
{
	t_dpoint		c2;
	t_rpoint		vc;
	t_rpoint		vr;
	t_rpoint		c;
	t_rpoint		s;

	vc = cy->vector;
	vr = ray.vector;
	c = ray.p;
	s = cy->summit;
	c2.x = (vr.z * vc.x) - (vr.x * vc.z);
	c2.y = (c.z * vc.x) + (s.x * vc.z) - (s.z * vc.x) - (c.x * vc.z);
	return (c2);
}

static t_dpoint	get_const3(t_ray ray, t_cylinder *cy)
{
	t_dpoint		c3;
	t_rpoint		vc;
	t_rpoint		vr;
	t_rpoint		c;
	t_rpoint		s;

	vc = cy->vector;
	vr = ray.vector;
	c = ray.p;
	s = cy->summit;
	c3.x = (vr.x * vc.y) - (vr.y * vc.x);
	c3.y = (c.x * vc.y) + (s.y * vc.x) - (s.x * vc.y) - (c.y * vc.x);
	return (c3);
}

t_rpoint		get_cyc_eq_factors(t_ray ray, t_cylinder *c)
{
	t_rpoint		f;
	t_dpoint		c1;
	t_dpoint		c2;
	t_dpoint		c3;

	c1 = get_const1(ray, c);
	c2 = get_const2(ray, c);
	c3 = get_const3(ray, c);
	f.x = (c1.x * c1.x) + (c2.x * c2.x) + (c3.x * c3.x);
	f.y = 2 * ((c1.x * c1.y) + (c2.x * c2.y) + (c3.x * c3.y));
	f.z = (c1.y * c1.y) + (c2.y * c2.y) + (c3.y * c3.y);
	f.z = f.z - pow((c->radius * vlength(c->vector)), 2);
	return (f);
}
