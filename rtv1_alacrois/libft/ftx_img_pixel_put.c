/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_img_pixel_put.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:07:41 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/24 18:42:42 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ftx_img_pixel_put(t_img *img, int x, int y, t_rgb color)
{
	if (img == NULL)
		return ;
	img->img_str[(y * img->line_size) + (x * 4)] = color.b;
	img->img_str[(y * img->line_size) + (x * 4) + 1] = color.g;
	img->img_str[(y * img->line_size) + (x * 4) + 2] = color.r;
	img->img_str[(y * img->line_size) + (x * 4) + 3] = color.trans;
}
