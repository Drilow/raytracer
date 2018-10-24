/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fcts_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:47:03 by alacrois          #+#    #+#             */
/*   Updated: 2018/05/27 16:28:22 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry/geometry.h>

t_rpoint		vnorm_to_length(t_rpoint v, double len)
{
	t_rpoint	new;

	v = vnorm(v);
	new.x = v.x * len;
	new.y = v.y * len;
	new.z = v.z * len;
	return (new);
}

double			vangle(t_rpoint v1, t_rpoint v2)
{
	double		angle;

	angle = acos(scalar(vnorm(v1), vnorm(v2)));
	return (angle);
}
