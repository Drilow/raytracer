/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:02:27 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 15:55:26 by cpays            ###   ########.fr       */
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

	angle = vangle(get_vector(c.p, lsrc), c.normal);
	if (c.o->type == 2 || c.o->type == 6 || c.o->type / 10 == 6)
		angle = PI - angle;
	if (angle < 0 || angle > PI)
		return (0);
	else if (angle > (PI / 2))
		return (0);
	af = ((PI / 2) - angle) / (PI / 2);
	return (af);
}

static t_rpoint		add_color(t_rpoint c, t_obj *o, t_light *l, double af)
{
	t_rpoint		new_c;
	t_rpoint		tmp_c;
	double			shining;

	shining = pow(af, 1 + SHINING_FACTOR);
	tmp_c = color_to_add(set_rpoint((double)o->color.r, (double)o->color.g, \
									(double)o->color.b), l->color, shining);
	tmp_c = set_rpoint(tmp_c.x * af * BRIGHTNESS, \
						tmp_c.y * af * BRIGHTNESS, \
						tmp_c.z * af * BRIGHTNESS);
	new_c = set_rpoint(c.x + tmp_c.x, c.y + tmp_c.y, c.z + tmp_c.z);
	return (new_c);
}

static void			get_color_core(t_obj *otmp, t_collision c, \
									t_light *l, t_light *tmpl)
{
	t_collision		tmpc;

	tmpc.o = otmp;
	if (otmp != c.o && collision(get_ray(c.p, get_vector(c.p, l->source)), \
		&tmpc) == true && deltasq(c.p, l->source) > deltasq(c.p, tmpc.p))
	{
		tmpl->color.r = (double)tmpl->color.r * \
						((double)otmp->color.trans / 255);
		tmpl->color.g = (double)tmpl->color.g * \
						((double)otmp->color.trans / 255);
		tmpl->color.b = (double)tmpl->color.b * \
						((double)otmp->color.trans / 255);
	}
}

static t_rpoint		init_color(t_obj *o)
{
	t_rpoint		color;
	t_rpoint		ocolor;

	ocolor = set_rpoint((double)o->color.r, \
						(double)o->color.g, (double)o->color.b);
	color = set_rpoint(ocolor.x * g_global.r.ambient_light.r * BRIGHTNESS, \
						ocolor.y * g_global.r.ambient_light.g * BRIGHTNESS, \
						ocolor.z * g_global.r.ambient_light.b * BRIGHTNESS);
	return (color);
}

t_rpoint			get_color(t_rt *r, t_collision c)
{
	t_rpoint		color;
	t_obj			*otmp;
	t_light			*l;
	t_light			tmpl;
	double			afactor;

	color = init_color(c.o);
	l = r->lights;
	while (l != NULL)
	{
		tmpl = *l;
		if (l->enabled == true)
		{
			otmp = r->objects;
			afactor = angle_factor(c, l->source);
			while (otmp != NULL)
			{
				get_color_core(otmp, c, l, &tmpl);
				otmp = otmp->next;
			}
			color = add_color(color, c.o, &tmpl, afactor);
		}
		l = l->next;
	}
	return (color);
}
