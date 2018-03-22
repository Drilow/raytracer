/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:43:20 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:44:10 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_tmp;

	s_tmp = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*s_tmp == (unsigned char)c)
			return ((void *)s_tmp);
		s_tmp++;
	}
	return (0);
}
