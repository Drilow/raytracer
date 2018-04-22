/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_img_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:46:58 by alacrois          #+#    #+#             */
/*   Updated: 2017/11/30 14:58:49 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ftx_img_clear(t_img *img, int size_x, int size_y)
{
	t_point	i;

	i.y = -1;
	while (++i.y < size_y)
	{
		i.x = -1;
		while (++i.x < size_x)
			ftx_img_pixel_put(img, i.x, i.y, ft_rgb(0, 0, 0, 0));
	}
}
