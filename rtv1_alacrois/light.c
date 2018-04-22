/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:21:23 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/02 21:01:52 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static double		angle_factor(t_obj *o, t_rpoint p, t_rpoint lsrc)
{
	double			angle;
	double			af;

	angle = vangle(get_vector(p, lsrc), normal_collision_vector(o, p));
	if (angle < 0 || angle > PI)
		return (AMBIENT_LIGHT);
	else if (angle > (PI / 2) && o->type == 2)
		angle = PI - angle;
	else if (angle > (PI / 2))
		return (AMBIENT_LIGHT);
	af = ((PI / 2) - angle) / (PI / 2);
	af = pow(af, (1 + SHINING_FACTOR));
	af = af + AMBIENT_LIGHT;
	return (af);
}

static t_rpoint		get_light_color(t_rtv1 *r, t_obj *o, t_rpoint p)
{
	t_rpoint		lc;
	t_rpoint		tmpp;
	t_obj			*otmp;
	t_light			*l;
	double			afactor;

	lc = set_rpoint(0, 0, 0);
	l = r->lights;
	while (l != NULL)
	{
		otmp = r->objects;
		afactor = angle_factor(o, p, l->source);
		while (otmp != NULL)
		{
			if (otmp != o && collision(get_ray(p, get_vector(p, l->source)), \
			otmp, &tmpp) == true && deltasq(p, l->source) > deltasq(p, tmpp))
				afactor = 0;
			otmp = otmp->next;
		}
		lc = set_rpoint(lc.x + ((double)l->color.r * afactor * BRIGHTNESS), \
		lc.y + ((double)l->color.g * afactor * BRIGHTNESS), \
		lc.z + ((double)l->color.b * afactor * BRIGHTNESS));
		l = l->next;
	}
	return (lc);
}

static t_rgb		get_color(t_rgb ocolor, t_rpoint lc, double df)
{
	t_rgb			color;
	t_rpoint		tmp;
	double			max;

	tmp = set_rpoint((double)ocolor.r * lc.x / df, \
		(double)ocolor.g * lc.y / df, (double)ocolor.b * lc.z / df);
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

t_rgb				get_ray_color(t_rtv1 *r, t_obj *o, t_rpoint p)
{
	t_rgb			color;
	t_rpoint		lc;
	double			distance_factor;

	lc = get_light_color(r, o, p);
	distance_factor = deltasq(r->cam_position, p) / LIGHT_DISTANCE_FACTOR;
	if (distance_factor < 1)
		distance_factor = 1;
	color = get_color(o->color, lc, distance_factor);
	return (color);
}
