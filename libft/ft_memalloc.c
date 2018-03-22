/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:43:04 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:44:17 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*s;
	char	*s1;

	s = (char *)malloc(sizeof(s) * size);
	if (s)
	{
		s1 = s;
		while (size > 0)
		{
			*s = 0;
			s++;
			size--;
		}
	}
	else
		return (NULL);
	return (s1);
}
