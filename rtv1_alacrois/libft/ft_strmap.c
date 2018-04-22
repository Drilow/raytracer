/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 15:55:20 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/04 08:18:29 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*s2;

	i = -1;
	if (s == NULL || f == NULL)
		return (NULL);
	s2 = (char *)malloc(sizeof(*s2) * (ft_strlen(s) + 1));
	while (s[++i])
		s2[i] = f(s[i]);
	s2[i] = '\0';
	return (s2);
}
