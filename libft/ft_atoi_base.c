/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:16:43 by adleau            #+#    #+#             */
/*   Updated: 2017/12/22 02:01:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_getter(char c, int base_limit)
{
	int		base_iterator;
	char	*base;

	base = ft_strdup("0123456789abcdef");
	base_iterator = -1;
	while (++base_iterator < base_limit)
	{
		if (base[base_iterator] == c ||
		((c >= 'A' && c <= 'F') && c + 32 == base[base_iterator]))
			return (base_iterator);
	}
	free(base);
	return (-1);
}

int			ft_atoi_base(const char *str, int str_base)
{
	int		nb;
	int		sign;
	int		i;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	i = -1;
	nb = 0;
	while (str[++i])
	{
		if (base_getter(str[i], str_base) == -1)
			return (nb * sign);
		nb = nb * str_base + base_getter(str[i], str_base);
	}
	return (nb * sign);
}
