/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_equation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 19:18:36 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/27 19:18:44 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double		delta(t_rpoint f)
{
	return ((f.y * f.y) - (4 * (f.x * f.z)));
}

t_bool				ft_solve_equation(t_rpoint factors, t_dpoint *result)
{
	double			d;

	d = delta(factors);
	if (d < 0)
		return (false);
	if (factors.x == 0)
	{
		if (factors.y == 0)
			return (false);
		result->x = -(factors.z / factors.y);
		result->y = result->x;
		return (true);
	}
	result->x = (-factors.y - sqrt(d)) / (2 * factors.x);
	result->y = (-factors.y + sqrt(d)) / (2 * factors.x);
	return (true);
}
