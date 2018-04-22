/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 18:47:35 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:27:25 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	size_t	i;

	str = b;
	i = 0;
	if (b == NULL)
		return (NULL);
	while (i < len)
	{
		*(str + i) = (unsigned char)c;
		i++;
	}
	return (b);
}
