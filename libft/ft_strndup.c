/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:48:07 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:42:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*str;
	size_t	i;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *s1++;
	return (str);
}
