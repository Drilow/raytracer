/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:49:06 by adleau            #+#    #+#             */
/*   Updated: 2017/11/08 19:57:24 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strtrim(const char *s)
{
	int		i;
	int		e;
	int		j;
	char	*dst;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	j = i;
	while (s[j] && s[j + 1])
		j++;
	e = j;
	while (s[e] == ' ' || s[e] == '\n' || s[e] == '\t')
		e--;
	if (!(dst = (char *)malloc(sizeof(char) * (j - (j - e) - i) + 2)))
		return (NULL);
	j = 0;
	while (i <= e)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (dst);
}
