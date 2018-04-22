/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 11:56:28 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/23 16:09:07 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ftx_draw_check(t_env *e, t_point a, t_point b, int color)
{
	if (ft_pntcmp(a, b) == 1)
	{
		ftx_draw_point(e, a.x, a.y, color);
		return (-1);
	}
	if (ft_deltasq(a, b) <= 2)
	{
		ftx_draw_point(e, a.x, a.y, color);
		ftx_draw_point(e, b.x, b.y, color);
		return (-1);
	}
	return (0);
}

static void		ftx_draw_init(t_point a, t_point b, t_point *d, t_point *i)
{
	d->x = 1;
	d->y = 1;
	if (b.x < a.x)
		d->x = -1;
	if (b.y < a.y)
		d->y = -1;
	i->x = 0;
	i->y = 0;
}

static t_point	ftx_draw_calcx(t_point i, t_point d, int difx, int dify)
{
	t_point	new_i;

	new_i.y = ((abs(i.x) * dify) / difx) * d.y;
	new_i.x = i.x + d.x;
	return (new_i);
}

static t_point	ftx_draw_calcy(t_point i, t_point d, int difx, int dify)
{
	t_point new_i;

	new_i.x = ((abs(i.y) * difx) / dify) * d.x;
	new_i.y = i.y + d.y;
	return (new_i);
}

void			ftx_draw_line(t_env *e, t_point a, t_point b, int color)
{
	t_point	i;
	t_point	d;
	int		difx;
	int		dify;
	int		xaxe;

	if (ftx_draw_check(e, a, b, color) != 0)
		return ;
	ftx_draw_init(a, b, &d, &i);
	difx = (b.x - a.x) * d.x;
	dify = (b.y - a.y) * d.y;
	xaxe = 1;
	if (((b.x - a.x) * d.x) < ((b.y - a.y) * d.y))
		xaxe = 0;
	while ((xaxe == 0 && (a.y + i.y) != b.y) || \
	(xaxe == 1 && (a.x + i.x) != b.x))
	{
		if (xaxe == 1)
			i = ftx_draw_calcx(i, d, difx, dify);
		else
			i = ftx_draw_calcy(i, d, difx, dify);
		ftx_draw_point(e, a.x + i.x, a.y + i.y, color);
	}
}
