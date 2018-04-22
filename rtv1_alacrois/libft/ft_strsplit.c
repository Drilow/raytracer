/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:18:37 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 21:14:48 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nextchar(char const *s, char c, int index, int id)
{
	while (s[index])
	{
		if (((s[index] == c) && (id == 1)) || ((s[index] != c) && (id != 1)))
			return (index);
		index++;
	}
	return (index);
}

static int		ft_splitnb(char const *s, char c)
{
	int		nb;
	int		i;
	size_t	len;

	nb = 0;
	i = ft_nextchar(s, c, 0, 0);
	len = ft_strlen(s);
	while (i != (int)len)
	{
		nb++;
		i = ft_nextchar(s, c, i, 1);
		i = ft_nextchar(s, c, i, 0);
	}
	return (nb);
}

static int		ft_splitlen(char const *s, char c, int start)
{
	int		i;

	i = 0;
	while ((s[start + i] != c) && (s[start + i] != '\0'))
		i++;
	return (i);
}

static char		*ft_split(char const *s, char c, int *index)
{
	char	*str;
	int		i;
	int		i2;

	i = *index;
	i = ft_nextchar(s, c, i, 0);
	if (s[i] == '\0')
		return (NULL);
	str = (char *)malloc(sizeof(*str) * (ft_splitlen(s, c, i) + 1));
	if (str == NULL)
		return (NULL);
	i2 = 0;
	while ((s[i + i2] != c) && (s[i + i2] != '\0'))
	{
		str[i2] = s[i + i2];
		i2++;
	}
	str[i2] = '\0';
	*index = ft_nextchar(s, c, (i + i2), 0);
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**strsp;
	int		*pi;
	int		i;
	int		istr;

	if (s == NULL)
		return (NULL);
	strsp = (char **)malloc(sizeof(char *) * (ft_splitnb(s, c) + 1));
	if (strsp == NULL)
		return (NULL);
	pi = &i;
	i = 0;
	istr = 0;
	strsp[istr] = ft_split(s, c, pi);
	while (strsp[istr] != NULL)
	{
		istr++;
		strsp[istr] = ft_split(s, c, pi);
	}
	strsp[istr] = (char *)malloc(sizeof(char));
	strsp[istr] = 0;
	return (strsp);
}
