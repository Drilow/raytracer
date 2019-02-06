/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:01:11 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/05 15:55:28 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>

static t_rpoint		average(t_rpoint a, t_rpoint b, double f)
{
	t_rpoint		average;

	average.x = (a.x * (1 - f)) + (b.x * f);
	average.y = (a.y * (1 - f)) + (b.y * f);
	average.z = (a.z * (1 - f)) + (b.z * f);
	return (average);
}

static double		rgb_min(t_rgb c)
{
	double			min;

	min = c.r;
	if (min == 0)
		min = c.g;
	if (min == 0)
		min = c.b;
	if (min == 0)
		return (1);
	if (c.g < min && c.g != 0)
		min = c.g;
	if (c.b < min && c.b != 0)
		min = c.b;
	return (min);
}

static double		rpoint_max(t_rpoint p)
{
	if (p.x < p.y)
		p.x = p.y;
	if (p.x < p.z)
		p.x = p.z;
	return (p.x);
}

t_rpoint			color_to_add(t_rpoint oclr, t_rgb lclr, double af)
{
	t_rpoint		tmp;
	t_rpoint		lclr_factors;
	t_rpoint		cta;

	lclr_factors.x = (double)lclr.r / rgb_min(lclr);
	lclr_factors.y = (double)lclr.g / rgb_min(lclr);
	lclr_factors.z = (double)lclr.b / rgb_min(lclr);
	tmp = set_rpoint((oclr.x * (double)lclr.r), \
					(oclr.y * (double)lclr.g), \
					(oclr.z * (double)lclr.b));
	cta = average(tmp, set_rpoint(rpoint_max(tmp) * lclr_factors.x,
									rpoint_max(tmp) * lclr_factors.y,
									rpoint_max(tmp) * lclr_factors.z), af);
	return (cta);
}
