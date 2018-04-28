/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:51:39 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 20:07:35 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <geometry/geometry.h>

t_rgb	ft_rgb(int r, int g, int b, int alpha)
{
	t_rgb	rgb;

	rgb.r = (char)r;
	rgb.g = (char)g;
	rgb.b = (char)b;
	rgb.trans = (char)alpha;
	return (rgb);
}

void			usage(char *s, int i)
{
	ft_putendl(s);
	ft_exit("usage : ./rtv1 [scene]", i);
}
