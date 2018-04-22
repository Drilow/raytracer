/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:31:49 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:17:02 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s2;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	s2 = ft_memalloc(len);
	s2 = ft_memcpy(s2, s, len);
	return (s2);
}
