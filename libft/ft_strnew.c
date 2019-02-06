/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:48:20 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:42:02 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	while (size > 0)
	{
		s[i] = '\0';
		i++;
		size--;
	}
	s[i] = '\0';
	return (s);
}
