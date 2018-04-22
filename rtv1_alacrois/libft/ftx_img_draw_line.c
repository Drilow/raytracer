/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_img_draw_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:34:47 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/05 17:23:32 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ftx_img_draw_check(t_img *img, t_point a, t_point b, \
				t_rgb color)
{
	if (ft_pntcmp(a, b) == 1)
		ftx_img_pixel_put(img, a.x, a.y, color);
	else if (ft_deltasq(a, b) <= 2)
	{
		ftx_img_pixel_put(img, a.x, a.y, color);
		ftx_img_pixel_put(img, b.x, b.y, color);
	}
	else
		return (0);
	return (-1);
}

static void		ftx_img_draw_init(t_point a, t_point b, t_point *sign, \
				t_point *index)
{
	sign->x = 1;
	sign->y = 1;
	if (b.x < a.x)
		sign->x = -1;
	if (b.y < a.y)
		sign->y = -1;
	index->x = 0;
	index->y = 0;
}

static int		on_linex(t_point a, t_point b, t_point index, t_point sign)
{
	if (sign.x == 1 && (a.x + index.x) <= b.x)
		return (1);
	else if (sign.x == -1 && (a.x + index.x) >= b.x)
		return (1);
	return (0);
}

static int		on_liney(t_point a, t_point b, t_point index, t_point sign)
{
	if (sign.y == 1 && (a.y + index.y) <= b.y)
		return (1);
	else if (sign.y == -1 && (a.y + index.y) >= b.y)
		return (1);
	return (0);
}

void			ftx_img_draw_line(t_img *img, t_point a, t_point b, t_rgb color)
{
	t_point		index;
	t_point		sign;
	t_point		len;
	int			xaxe;

	if (ftx_img_draw_check(img, a, b, color) != 0)
		return ;
	ftx_img_draw_init(a, b, &sign, &index);
	len = ft_point((b.x - a.x) * sign.x, (b.y - a.y) * sign.y);
	xaxe = 1;
	if (len.y > len.x)
		xaxe = 0;
	while ((xaxe == 1 && on_linex(a, b, index, sign) == 1) || \
	(xaxe == 0 && on_liney(a, b, index, sign) == 1))
	{
		ftx_img_pixel_put(img, a.x + index.x, a.y + index.y, color);
		if (xaxe == 1)
			index = ft_point(index.x + sign.x, \
			((ft_abs(index.x + sign.x) * len.y) / len.x) * sign.y);
		else
			index = ft_point(((ft_abs(index.y + sign.y) * len.x) / len.y) \
			* sign.x, index.y + sign.y);
	}
}
