/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:46:38 by adleau            #+#    #+#             */
/*   Updated: 2017/12/19 09:39:02 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		return (NULL);
	}
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}
