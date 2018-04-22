/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 16:29:09 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/22 15:38:02 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_varinit(char **s, int *i, char *src, char *addon)
{
	*i = 0;
	*s = ft_strnew((ft_strlen(src) + ft_strlen(addon) + 1));
}

char		*ft_strins(char *src, char *addon, int index)
{
	int		i;
	char	*s;

	ft_varinit(&s, &i, src, addon);
	if (index > (int)ft_strlen(src))
		return (NULL);
	while (i < index)
	{
		s[i] = src[i];
		i++;
	}
	i = 0;
	while (addon[i])
	{
		s[index + i] = addon[i];
		i++;
	}
	i = index + i;
	while (src[index])
	{
		s[i] = src[index];
		i++;
		index++;
	}
	return (s);
}
