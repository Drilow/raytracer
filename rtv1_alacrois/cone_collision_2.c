/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_collision_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:32:40 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/27 16:32:47 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_dpoint	get_spf_constants(t_ray ray, t_cone *cone)
{
	t_dpoint		constants;
	t_rpoint		c;
	t_rpoint		s;
	t_rpoint		cv;
	t_rpoint		rv;

	c = ray.p;
	s = cone->summit;
	cv = cone->vector;
	rv = ray.vector;
	constants.x = (cv.x * rv.x) + (cv.y * rv.y) + (cv.z * rv.z);
	constants.y = (cv.x * c.x) + (cv.y * c.y) + (cv.z * c.z) - \
	(cv.x * s.x) - (cv.y * s.y) - (cv.z * s.z);
	return (constants);
}

static t_rpoint	get_scalar_product_factors(t_ray ray, t_cone *cone)
{
	t_rpoint		spf;
	t_dpoint		spf_c;

	spf_c = get_spf_constants(ray, cone);
	spf.x = spf_c.x * spf_c.x;
	spf.y = 2 * spf_c.x * spf_c.y;
	spf.z = spf_c.y * spf_c.y;
	return (spf);
}

static t_rpoint	get_magnitude_product_factors(t_ray ray, t_cone *cone)
{
	t_rpoint		mpf;
	t_rpoint		c;
	t_rpoint		s;
	t_rpoint		v;

	c = ray.p;
	s = cone->summit;
	v = ray.vector;
	mpf.x = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	mpf.x = mpf.x * pow(vlength(cone->vector), 2);
	mpf.y = 2 * ((v.x * c.x) - (s.x * v.x) + \
	(v.y * c.y) - (s.y * v.y) + \
	(v.z * c.z) - (s.z * v.z));
	mpf.y = mpf.y * pow(vlength(cone->vector), 2);
	mpf.z = (c.x * c.x) + (c.y * c.y) + (c.z * c.z) + \
	(s.x * s.x) + (s.y * s.y) + (s.z * s.z) - \
	(2 * ((s.x * c.x) + (s.y * c.y) + (s.z * c.z)));
	mpf.z = mpf.z * pow(vlength(cone->vector), 2);
	return (mpf);
}

t_bool			get_cc_eq_factors(t_ray ray, t_cone *c, t_rpoint *f)
{
	t_rpoint		scp;
	t_rpoint		mp;

	scp = get_scalar_product_factors(ray, c);
	mp = get_magnitude_product_factors(ray, c);
	f->x = scp.x - (pow(cos(c->angle), 2) * mp.x);
	f->y = scp.y - (pow(cos(c->angle), 2) * mp.y);
	f->z = scp.z - (pow(cos(c->angle), 2) * mp.z);
	return (true);
}
