/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:47:25 by adleau            #+#    #+#             */
/*   Updated: 2017/11/08 18:45:44 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*s1;
	char	*s2;

	if (!f || !(s1 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	s2 = s1;
	while (*s != '\0')
		*s1++ = f(*s++);
	*s1 = '\0';
	return (s2);
}
