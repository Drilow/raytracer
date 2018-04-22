/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:29:04 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:28:28 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	len;

	if (dest == NULL || src == NULL)
		return (NULL);
	len = ft_strlen(src);
	if (n <= len)
		dest = ft_memcpy(dest, src, n);
	else
	{
		dest = ft_memcpy(dest, src, len);
		len--;
		while (++len < n)
			dest[len] = 0;
	}
	return (dest);
}
