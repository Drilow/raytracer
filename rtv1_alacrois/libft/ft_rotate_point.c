/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 12:00:28 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/24 19:32:14 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rotate_point(t_3dpoint *point, char axis, double angle)
{
	t_point		ddpoint;

	if (axis == 'x')
	{
		ddpoint.x = point->z;
		ddpoint.y = point->y;
		point->z = ddpoint.x * cos(angle) - ddpoint.y * sin(angle);
		point->y = ddpoint.x * sin(angle) + ddpoint.y * cos(angle);
	}
	if (axis == 'y')
	{
		ddpoint.x = point->x;
		ddpoint.y = point->z;
		point->x = ddpoint.x * cos(angle) - ddpoint.y * sin(angle);
		point->z = ddpoint.x * sin(angle) + ddpoint.y * cos(angle);
	}
	if (axis == 'z')
	{
		ddpoint.x = point->y;
		ddpoint.y = point->x;
		point->y = ddpoint.x * cos(angle) - ddpoint.y * sin(angle);
		point->x = ddpoint.x * sin(angle) + ddpoint.y * cos(angle);
	}
}
