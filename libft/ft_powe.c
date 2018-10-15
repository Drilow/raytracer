/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:23:55 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/15 11:50:07 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_powe(double nb)
{
	double	ret;
	double	save;

	ret = nb;
	save = nb;
	while (nb > 0 && nb--)
		ret *= 10;
	while (nb < 0 && nb++)
		ret /= 10;
	return (ret / save);
}
