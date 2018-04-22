/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 14:51:00 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 04:32:14 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strstrlen(char const **s)
{
	size_t	i;

	i = 0;
	if (s != NULL && *s != NULL)
	{
		while (s[i] != NULL)
			i++;
	}
	return (i);
}
