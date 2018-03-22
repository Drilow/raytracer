/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:47:32 by adleau            #+#    #+#             */
/*   Updated: 2017/11/08 18:48:43 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	char	*s2;
	int		i;

	if (!f || !(s1 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	s2 = s1;
	while (*s != '\0')
	{
		*s1++ = f(i, *s++);
		i++;
	}
	*s1 = '\0';
	return (s2);
}
