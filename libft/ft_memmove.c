/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:43:59 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:43:54 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*c1;
	char	*c2;

	if (n == 0)
		return (s1);
	if (s1 <= s2)
		return (ft_memcpy(s1, s2, n));
	c1 = (char *)s1 + n;
	c2 = (char *)s2 + n;
	while (n-- > 0)
		*--c1 = *--c2;
	return (s1);
}
