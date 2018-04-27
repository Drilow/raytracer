/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:21:23 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/22 19:10:20 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//static double		angle_factor(t_obj *o, t_rpoint p, t_rpoint lsrc)
static double		angle_factor(t_collision c, t_rpoint lsrc)
{
	double			angle;
	double			af;

	angle = vangle(get_vector(c.p, lsrc), normal_collision_vector(c));
	if (angle < 0 || angle > PI)
		return (AMBIENT_LIGHT);
	else if (angle > (PI / 2) && c.o->type == 2)
		angle = PI - angle;
	else if (angle > (PI / 2))
		return (AMBIENT_LIGHT);
	af = ((PI / 2) - angle) / (PI / 2);
//	af = pow(af, (1 + SHINING_FACTOR));
//	af = af + AMBIENT_LIGHT;
	return (af);
}

static t_rpoint		add_color(t_rpoint lc, t_light *l, double afactor)
{
	t_rpoint		new_lc;
	t_rpoint		diff;
	t_rpoint		tmp_lc;
	double			max;

	tmp_lc = set_rpoint(((double)l->color.r * afactor * BRIGHTNESS), \
						((double)l->color.g * afactor * BRIGHTNESS), \
						((double)l->color.b * afactor * BRIGHTNESS));
	max = tmp_lc.x;
	if (max < tmp_lc.y)
        max = tmp_lc.y;
    if (max < tmp_lc.z)
        max = tmp_lc.z;
	diff.x = max - tmp_lc.x;
	diff.y = max - tmp_lc.y;
	diff.z = max - tmp_lc.z;
	afactor = 1;
	tmp_lc = set_rpoint(tmp_lc.x + (diff.x * pow(afactor, 1)),	\
						tmp_lc.y + (diff.y * pow(afactor, 1)),	\
						tmp_lc.z + (diff.z * pow(afactor, 1)));
	new_lc = set_rpoint(lc.x + tmp_lc.x, lc.y + tmp_lc.y, lc.z + tmp_lc.z);
	return (new_lc);
}

//static t_rpoint		get_light_color(t_rtv1 *r, t_obj *o, t_rpoint p)
static t_rpoint		get_light_color(t_rtv1 *r, t_collision c)
{
	t_rpoint		lc;
//	t_light_clr		lc;
//	t_rpoint		tmpp;
	t_obj			*otmp;
	t_light			*l;
	double			afactor;
	t_collision		tmpc;

//	lc.clr = set_rpoint(0, 0, 0);
	lc = set_rpoint(0, 0, 0);
//	lc.shining = 0;
	l = r->lights;
	while (l != NULL)
	{
		otmp = r->objects;
//		afactor = angle_factor(c.o, c.p, l->source);
		afactor = angle_factor(c, l->source);
		while (otmp != NULL)
		{
//			if (otmp != c.o && collision(get_ray(c.p, get_vector(c.p, l->source)), \
//			otmp, &tmpp) == true && deltasq(c.p, l->source) > deltasq(c.p, tmpp))
			tmpc.o = otmp;
//			tmpc.p = tmpp;
			if (otmp != c.o && collision(get_ray(c.p, get_vector(c.p, l->source)), &tmpc) == true && deltasq(c.p, l->source) > deltasq(c.p, tmpc.p))
				afactor = 0;
			otmp = otmp->next;
		}
//		lc.clr = add_color(lc, l, afactor);
		lc = add_color(lc, l, afactor);
//		lc.shining = (lc.shining + afactor) / 2;
/*
		lc = set_rpoint(lc.x + ((double)l->color.r * afactor * BRIGHTNESS), \
		lc.y + ((double)l->color.g * afactor * BRIGHTNESS), \
		lc.z + ((double)l->color.b * afactor * BRIGHTNESS));
*/
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

//t_rgb				get_ray_color(t_rtv1 *r, t_obj *o, t_rpoint p)
t_rgb				get_ray_color(t_rtv1 *r, t_collision c)
{
	t_rgb			color;
	t_rpoint		lc;
//	t_light_clr		lc;
	double			distance_factor;

//	lc = get_light_color(r, c.o, c.p);
	lc = get_light_color(r, c);
	distance_factor = deltasq(r->cam_position, c.p) / LIGHT_DISTANCE_FACTOR;
	if (distance_factor < 1)
		distance_factor = 1;
	color = get_color(c.o->color, lc, distance_factor);
	return (color);
}
