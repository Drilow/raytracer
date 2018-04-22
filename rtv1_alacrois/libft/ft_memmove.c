/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 03:11:05 by alacrois          #+#    #+#             */
/*   Updated: 2017/07/26 03:33:57 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	buf[len];

	i = -1;
	while (++i < len)
		buf[i] = *((char *)src + (i * sizeof(char)));
	i = -1;
	while (++i < len)
		*((char *)dst + (i * sizeof(char))) = buf[i];
	return (dst);
}
