/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getspaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 03:17:09 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 03:17:44 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getspaces(int n)
{
	int		i;
	char	*spaces;

	spaces = ft_strnew(n + 1);
	if (spaces == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ft_strcat(spaces, " ");
		i++;
	}
	return (spaces);
}
