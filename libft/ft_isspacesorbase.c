/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspacesorbase.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:29:35 by adleau            #+#    #+#             */
/*   Updated: 2017/12/22 02:02:31 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uint				ft_isspace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
	c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

t_uint				ft_is_base(char c, char *base)
{
	while (*base)
	{
		if (c == *base)
			return (1);
		++base;
	}
	return (0);
}
