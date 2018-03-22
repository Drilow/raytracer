/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:48:29 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:41:57 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		len;
	size_t		i;

	len = ft_strlen(s1);
	len = ft_strlen(s2);
	if (!n)
		return (NULL);
	if (len > n)
		return (NULL);
	if (len == 0)
		return ((char*)s1);
	if (!*s2)
		return (NULL);
	i = 0;
	while (*s1 && i <= (n - len))
	{
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char *)s1);
		s1++;
		i++;
	}
	return (NULL);
}
