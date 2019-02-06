/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:49:08 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:47:26 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

extern t_global g_global;

static	int			check_key(char *str)
{
	if (cmp_chars(str, "pos", 0))
		return (1);
	if (cmp_chars(str, "angle", 0))
		return (2);
	return (0);
}

static	t_rpoint	camera_init(void)
{
	t_rpoint	angle;

	g_global.r.cam_position.x = 0;
	g_global.r.cam_position.y = 0;
	g_global.r.cam_position.z = 0;
	angle.x = 0;
	angle.y = 0;
	angle.z = 0;
	return (angle);
}

static	t_rpoint	put_cam_info(t_json_array *arr)
{
	int				*a;
	unsigned long	num;
	t_rpoint		points;

	num = 0;
	points.x = 0;
	points.y = 0;
	points.z = 0;
	if (arr->nb == 3 && check_arr(arr))
	{
		a = (int *)arr->value[num++]->ptr;
		points.x = (double)*a;
		a = (int *)arr->value[num++]->ptr;
		points.y = (double)*a;
		a = (int *)arr->value[num]->ptr;
		points.z = (double)*a;
		return (points);
	}
	return (points);
}

static	void		*get_info(t_json_value *val, int i, t_rpoint *angle)
{
	t_json_array	*arr;
	unsigned long	num;

	num = 0;
	if (val->type != 3)
		return (NULL);
	arr = (t_json_array *)val->ptr;
	if (i == 1)
		if (arr->nb == 3)
			g_global.r.cam_position = put_cam_info(arr);
	if (i == 2)
		if (arr->nb == 3)
			*angle = put_cam_info(arr);
	return (NULL);
}

void				parse_camera(t_json_object *obj, unsigned long nb)
{
	t_json_object	*o;
	unsigned long	num;
	t_rpoint		angle;

	num = 0;
	angle = camera_init();
	if (obj->pair[nb]->value->type != 4)
	{
		set_camera(angle);
		return ;
	}
	if ((o = (t_json_object *)obj->pair[nb]->value->ptr) == NULL)
	{
		set_camera(angle);
		return ;
	}
	while (num < o->nb)
	{
		if ((check_key(o->pair[num]->key->str)) == 1)
			get_info(o->pair[num]->value, 1, &angle);
		else if ((check_key(o->pair[num]->key->str) == 2))
			get_info(o->pair[num]->value, 2, &angle);
		num++;
	}
	set_camera(angle);
}
