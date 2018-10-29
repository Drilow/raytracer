/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:49:08 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/29 16:11:31 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>
#include <extra/extra_defs.h>
#include <objects/object.h>
#include <fcntl.h>

extern t_global g_global;

static	int		check_key(char *str)
{
	if (cmp_chars(str, "pos", 0))
		return (1);
	if (cmp_chars(str, "angle", 0))
		return (2);
	return (0)
}

static 	t_rpoint	camera_init(void)
{
	t_rpoint	angle;

	g_global.r->cam_position.x = -20;
	g_global.r->cam_position.y = 0;
	g_global.r->cam_position.z = -30;
	angle.x = 0;
	angle.y = -10;
	angle.z = 0;
	return(angle);
}

static 	t_rpoint		put_cam_info(t_json_array *arr)
{
	int				*a;
	unsigned long	*num;
	t_rpoint		points;

	num = 0;
	if (arr->nb == 3)
	{
		a = (int *)arr->value[num++]->ptr;
		points.x = (double)*a;
		a = (int *)arr->value[num++]->ptr;
		points.y = (double)*a;
		a = (int *)arr->value[num]->ptr;
		points.z = (double)*a;
		return (points);
	}
	return (NULL);
}

static	void	*get_info(t_json_value *val, int i, t_rpoint *angle)
{
	t_json_array	*arr;
	unsigned long	num;

	num = 0;
	if (val->type != array)
		return (NULL);
	arr = (t_json_array *)val->ptr;
	if (i == 1)
		if (arr->nb == 3)
			g_global.r->cam_position = put_cam_info(arr);
	if (i == 2)
		if (arr->nb == 3)
			*angle = put_cam_info(arr);
	return (NULL);
}

void				*parse_camera(t_json_object *obj, unsigned long nb)
{
	t_json_object	*o;
	unsigned long	num;
	t_rpoint		angle

	num = 0;
	o = 0;
	angle = camera_init();
	if (obj->pair[nb]->value->type != 4)
		return (set_camera(angle));
	if((o = (t_json_object *)obj->pair[nb]->value->ptr) == NULL)
		return (set_camera(angle));
	while (num++ < o->nb)
	{
		if ((check_key(obj->pair[num]->key->str)) == 1)
			get_info(obj->pair[num]->value, 1, &angle);
		if ((check_key(obj->pair[num]->key->str)) == 2)
			get_info(obj->pair[num]->value, 2, &angle);
	}
	return(set_camera(angle));
}
