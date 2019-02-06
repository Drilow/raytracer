/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:45:24 by alacrois          #+#    #+#             */
/*   Updated: 2019/01/29 17:34:40 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <geometry/geometry.h>

static void		rotate_2d(double *x, double *y, t_dpoint xy, double angle)
{
	*x = (xy.x * cos(angle)) - (xy.y * sin(angle));
	*y = (xy.x * sin(angle)) + (xy.y * cos(angle));
}

void			rotate(t_rpoint *p, t_rpoint angle)
{
	t_dpoint	tmp;

	if (angle.x != 0)
	{
		tmp.x = p->z;
		tmp.y = p->y;
		rotate_2d(&(p->z), &(p->y), tmp, angle.x);
	}
	if (angle.y != 0)
	{
		tmp.x = p->x;
		tmp.y = p->z;
		rotate_2d(&(p->x), &(p->z), tmp, angle.y);
	}
	if (angle.z != 0)
	{
		tmp.x = p->y;
		tmp.y = p->x;
		rotate_2d(&(p->y), &(p->x), tmp, angle.z);
	}
}

static void		rotate_poly_obj(t_obj *o, t_rpoint angle)
{
	t_vertex	*tmpv;
	t_poly_obj	*tmppo;

	tmppo = (t_poly_obj *)o->obj;
	while (tmppo != NULL)
	{
		tmpv = tmppo->vertices;
		rotate(&(tmpv->pl.vector), angle);
		while (tmpv != NULL)
		{
			rotate(&(tmpv->p), angle);
			tmpv = tmpv->next;
		}
		tmppo = tmppo->next;
	}
}

void			rotate_obj(void *o, int type, t_rpoint angle)
{
	t_obj		*obj;

	if (type != 0)
		obj = (t_obj *)o;
	if (type == 2)
		rotate(&(((t_plane *)obj->obj)->vector), angle);
	if (type == 3)
		rotate(&(((t_cone *)obj->obj)->vector), angle);
	if (type == 4)
		rotate(&(((t_cylinder *)obj->obj)->vector), angle);
	if (type == 6 || type / 10 == 6)
	{
		((t_poly_obj *)obj->obj)->rotation = angle;
		rotate_poly_obj(obj, angle);
	}
}

void			translate_obj(void *o, int type, t_rpoint translation)
{
	t_rpoint	*data;

	if (type == 0)
		data = &(((t_light *)o)->source);
	else
		data = &(((t_obj *)o)->position);
	data->x = data->x + translation.x;
	data->y = data->y + translation.y;
	data->z = data->z + translation.z;
}
