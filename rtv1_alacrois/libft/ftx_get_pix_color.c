/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_get_pix_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:09:50 by alacrois          #+#    #+#             */
/*   Updated: 2018/01/26 15:10:17 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rgb		ftx_get_pix_color(t_img *img, int x, int y)
{
	t_rgb	c;

	c = ft_rgb(0, 0, 0, 0);
	if (img == NULL)
		return (c);
	c.b = img->img_str[(y * img->line_size) + (x * 4)];
	c.g = img->img_str[(y * img->line_size) + (x * 4) + 1];
	c.r = img->img_str[(y * img->line_size) + (x * 4) + 2];
	c.trans = img->img_str[(y * img->line_size) + (x * 4) + 3];
	return (c);
}
