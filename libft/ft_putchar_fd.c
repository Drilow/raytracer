/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:44:25 by adleau            #+#    #+#             */
/*   Updated: 2017/11/08 19:43:14 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	conversion(int c, int ref, int i, int fd)
{
	int		tab[32];

	while (--i >= 0)
	{
		if (i % 8 == 1 && i != 1)
			tab[i] = 0;
		else if ((ref >= 15 && i == 1) || (ref >= 23 && i == 2) ||
		(ref == 31 && i == 3) || (i != ref && !(i % 8)))
			tab[i] = 1;
		else
		{
			tab[i] = c % 2;
			c /= 2;
		}
	}
	while (++i <= ref + 1)
	{
		if (i != 0 && !(i % 8))
		{
			write(fd, &c, 1);
			c = 0;
		}
		c += tab[i] * ft_pow(2, 7 - (i % 8));
	}
}

void		ft_putchar_fd(int c, int fd)
{
	if (c <= 127)
		write(fd, &c, 1);
	else if (c > 127 && c < 2048)
		conversion(c, 15, 16, fd);
	else if (c >= 2048 && c < 65536)
		conversion(c, 23, 24, fd);
	else if (c >= 65536 && c < 2097152)
		conversion(c, 31, 32, fd);
}
