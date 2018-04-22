/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 19:19:43 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:57:08 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if ((s1 == NULL || s2 == NULL) && (n > 0))
	{
		if (s1 == s2)
			return (0);
		else if (s1 == NULL)
			return (0 - (unsigned char)*s2);
		else
			return ((unsigned char)*s1);
	}
	i = 0;
	while (((s1[i]) || (s2[i])) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
