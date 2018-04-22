/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:17:22 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/25 18:42:35 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	if (size < 1)
		return (NULL);
	mem = (void *)malloc(size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*((char *)mem + i) = 0;
		i++;
	}
	return (mem);
}
