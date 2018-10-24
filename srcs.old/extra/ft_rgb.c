/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:51:39 by alacrois          #+#    #+#             */
/*   Updated: 2018/05/17 19:35:00 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <geometry/geometry.h>

t_rgb	ft_rgb(int r, int g, int b, int alpha)
{
	t_rgb	rgb;

	rgb.r = (unsigned char)r;
	rgb.g = (unsigned char)g;
	rgb.b = (unsigned char)b;
	rgb.trans = (unsigned char)alpha;
	return (rgb);
}

void			usage(char *s, int i)
{
	ft_putendl(s);
	ft_exit("usage : ./rtv1 [scene]", i);
}
