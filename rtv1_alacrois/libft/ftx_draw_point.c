/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_draw_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 11:55:26 by alacrois          #+#    #+#             */
/*   Updated: 2015/05/06 11:55:53 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ftx_draw_point(t_env *e, int x, int y, int color)
{
	mlx_pixel_put(e->mlx, e->win, x, y, color);
}
