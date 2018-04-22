/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:13:20 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/17 17:46:40 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		i2;

	if (s1 == NULL || s2 == NULL)
	{
		if (s1 != NULL)
			return (ft_strdup(s1));
		if (s2 != NULL)
			return (ft_strdup(s2));
		return (NULL);
	}
	s3 = (char *)malloc(sizeof(*s3) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	i = -1;
	i2 = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++i2])
		s3[i + i2] = s2[i2];
	s3[i + i2] = '\0';
	return (s3);
}
