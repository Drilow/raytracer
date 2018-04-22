/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:31:00 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:16:22 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	len;

	if (dest == NULL || src == NULL)
		return (NULL);
	len = ft_strlen(src) + 1;
	dest = ft_memcpy(dest, src, len);
	return (dest);
}
