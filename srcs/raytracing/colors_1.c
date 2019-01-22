/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:00:10 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/22 11:35:16 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>

extern t_global g_global;

static t_rgb		get_final_color(t_rpoint c, double df)
{
	t_rgb			color;
	t_rpoint		tmp;
	double			max;

	max = 0;
	tmp = set_rpoint(c.x / df, c.y / df, c.z / df);
	max = tmp.x;
	if (max < tmp.y)
		max = tmp.y;
	if (max < tmp.z)
		max = tmp.z;
	if (max <= 255)
	{
		color = ft_rgb((unsigned char)tmp.x, (unsigned char)tmp.y, \
		(unsigned char)tmp.z, 0);
		return (color);
	}
	color.r = (unsigned char)((tmp.x / max) * 255);
	color.g = (unsigned char)((tmp.y / max) * 255);
	color.b = (unsigned char)((tmp.z / max) * 255);
	color.trans = 0;
	return (color);
}

static t_rgb		average_color(t_rgb c1, t_rgb c2, unsigned int trans)
{
	t_rgb			new;

	new.r = (unsigned int)((double)((double)c1.r * \
			(255 - (double)trans) + (double)c2.r * (double)trans) / 255);
	new.b = (unsigned int)((double)((double)c1.b * \
			(255 - (double)trans) + (double)c2.b * (double)trans) / 255);
	new.g = (unsigned int)((double)((double)c1.g * \
			(255 - (double)trans) + (double)c2.g * (double)trans) / 255);
	new.trans = 0;
	return (new);
}

t_rgb				get_ray_color(t_rt *r, t_collision *c)
{
	t_rgb			color;
	t_rpoint		tmp_color;
	double			distance_factor;

	if (c == NULL)
		return (ft_rgb(0, 0, 0, 0));
	tmp_color = get_color(r, *c);
	distance_factor = deltasq(r->cam_position, c->p) / LIGHT_DISTANCE_FACTOR;
	if (LIGHT_LOSS == false || distance_factor < 1)
		distance_factor = 1;
	color = get_final_color(tmp_color, distance_factor);
	if (REFLEX_DEPTH > 0 && c->o->reflex > 0)
		color = average_color(color, \
				get_ray_color(r, c->reflected), c->o->reflex);
	if (c->o->color.trans > 0)
		color = average_color(color, \
				get_ray_color(r, c->next), c->o->color.trans);
	return (color);
}
