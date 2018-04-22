/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 03:14:52 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 03:14:56 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getdigit(int nb, int index)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = ft_abs(nb);
	while (tmp > 9)
	{
		tmp = tmp / 10;
		i++;
	}
	i++;
	tmp = nb;
	if (index > i || index < 1)
		return (-1);
	while (i > index)
	{
		tmp = tmp / 10;
		i--;
	}
	return (tmp % 10);
}
