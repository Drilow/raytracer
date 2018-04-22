/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:36:33 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:25:55 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*uc_dst;
	const unsigned char	*uc_src;

	i = 0;
	if (dst == NULL || src == NULL)
		return (NULL);
	uc_dst = dst;
	uc_src = src;
	while (i < n)
	{
		uc_dst[i] = uc_src[i];
		if (uc_src[i] == (unsigned char)c)
			return (uc_dst + i + 1);
		i++;
	}
	return (NULL);
}
