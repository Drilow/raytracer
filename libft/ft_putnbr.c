/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:44:53 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:43:35 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_aff(int nb, int signe)
{
	if (nb / 10)
		ft_aff(nb / 10, signe);
	ft_putchar('0' + signe * (nb % 10));
}

void			ft_putnbr(int n)
{
	int		signe;

	signe = 1;
	if (n < 0)
	{
		ft_putchar('-');
		signe = -1;
	}
	ft_aff(n, signe);
}
