/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:43:27 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:44:05 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*c1;
	const unsigned char	*c2;

	while (n > 0)
	{
		c1 = (unsigned char *)s1;
		c2 = (unsigned char *)s2;
		if (*c1 != *c2)
			return (*c1 - *c2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
