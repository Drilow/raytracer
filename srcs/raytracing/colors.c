/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:21:23 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/14 16:22:17 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracing/collision.h>
#include <global.h>
#include <extra/extra_defs.h>

extern t_global g_global;

static double		angle_factor(t_collision c, t_rpoint lsrc)
{
	double			angle;
	double			af;

	angle = vangle(get_vector(c.p, lsrc), normal_collision_vector(c));
	if (angle < 0 || angle > PI)
		return (0);
//		return (AMBIENT_LIGHT);
	else if (angle > (PI / 2) && c.o->type == 2)
		angle = PI - angle;
	else if (angle > (PI / 2))
		return (0);
//		return (AMBIENT_LIGHT);
	af = ((PI / 2) - angle) / (PI / 2);
	return (af);
}

// Moyenne entre 2 couleurs a et b selon une ponderation indique par f (entre 0 et 1)
// 0 -> a, 1 -> b
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
	if (c.r > c.g)
		c.r = c.g;
	if (c.r > c.b)
		c.r = c.b;
	return ((double)c.r);
}

static double		rpoint_max(t_rpoint p)
{
	if (p.x < p.y)
		p.x = p.y;
    if (p.x < p.z)
		p.x = p.z;
    return (p.x);
}

static t_rpoint		color_to_add(t_rpoint oclr, t_rgb lclr, double af)
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

static t_rpoint		add_color(t_rpoint c, t_rpoint oclr, t_light *l, double af)
{
	t_rpoint		new_c;
	t_rpoint		tmp_c;
	double			shining;

	shining = pow(af, 1 + SHINING_FACTOR);
	tmp_c = color_to_add(oclr, l->color, shining);
	tmp_c = set_rpoint(tmp_c.x * af * BRIGHTNESS + g_global.r->ambient_light.r, \
					   tmp_c.y * af * BRIGHTNESS + g_global.r->ambient_light.g, \
					   tmp_c.z * af * BRIGHTNESS + g_global.r->ambient_light.b);
/*
	tmp_c = set_rpoint(tmp_c.x * af * BRIGHTNESS, \
                       tmp_c.y * af * BRIGHTNESS, \
                       tmp_c.z * af * BRIGHTNESS);
*/
	new_c = set_rpoint(c.x + tmp_c.x, c.y + tmp_c.y, c.z + tmp_c.z);
	return (new_c);
}

static t_rpoint		get_color(t_rt *r, t_collision c, bool debug)
{
	t_rpoint		color;
	t_rpoint		ocolor;
	t_obj			*otmp;
	t_light			*l;
	double			afactor;
	t_collision		tmpc;

	color = set_rpoint(0, 0, 0);
	ocolor = set_rpoint((double)c.o->color.r, (double)c.o->color.g, \
						(double)c.o->color.b);
	l = r->lights;
	while (l != NULL)
	{
		if (l->enabled == true)
		{
		otmp = r->objects;
		afactor = angle_factor(c, l->source);
		if (debug == true)
            printf("afactor = %f\n", afactor);
		while (otmp != NULL)
		{
			tmpc.o = otmp;
			if (otmp != c.o && collision(get_ray(c.p, get_vector(c.p, l->source)), &tmpc, debug) == true && deltasq(c.p, l->source) > deltasq(c.p, tmpc.p))
			{
				afactor = 0;
//				if (debug == true)
//				{
//					printf("collision ! obj type = %d\n", otmp->type);
//				}
			}
			otmp = otmp->next;
		}
		color = add_color(color, ocolor, l, afactor);
		}
		l = l->next;
	}
//	if (debug == true)
//		printf("\n");
	return (color);
}

static t_rgb		get_final_color(t_rpoint c, double df)
{
	t_rgb			color;
	t_rpoint		tmp;
	double			max;

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

t_rgb				get_ray_color(t_rt *r, t_collision c, bool debug)
{
	t_rgb			color;
	t_rpoint		tmp_color;
	double			distance_factor;
	t_point			checker;

	checker.x = -1;
	checker.y = -1;
	tmp_color = get_color(r, c, debug);
//	if (debug == true)
//		printf("get_ray_color : rgb(%f, %f, %f)\n", tmp_color.x, tmp_color.y, tmp_color.z);
	distance_factor = deltasq(r->cam_position, c.p) / LIGHT_DISTANCE_FACTOR;
//	if (distance_factor < 1)
		distance_factor = 1;
	color = get_final_color(tmp_color, distance_factor);
//	if (c.o->type == 2 && color.g < 50)
//		printf("Olalala !\n");
	return (color);
}
