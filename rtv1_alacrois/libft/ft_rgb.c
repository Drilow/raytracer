/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:51:39 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/25 16:53:03 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rgb	ft_rgb(int r, int g, int b, int alpha)
{
	t_rgb	rgb;

	rgb.r = (char)r;
	rgb.g = (char)g;
	rgb.b = (char)b;
	rgb.trans = (char)alpha;
	return (rgb);
}
