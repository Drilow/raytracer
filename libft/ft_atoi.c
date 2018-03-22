/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:40:35 by adleau            #+#    #+#             */
/*   Updated: 2017/12/22 02:02:05 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				check_size(const char *str, int sign)
{
	unsigned long long	a;

	a = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			a = a * 10 + ((unsigned long long)*str - '0');
		else
			return (a * sign);
		str++;
	}
	if (a - 9223372036854775807 > 0 && sign == 1)
		return (-1);
	if (a - 9223372036854775807 > 1 && sign == -1)
		return (0);
	return (1);
}

int						ft_atoi(const char *str)
{
	int					val;
	int					sign;

	sign = 1;
	val = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (ft_strlen(str) > 18)
		if (check_size(str, sign) != 1)
			return (check_size(str, sign));
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			val = val * 10 + ((int)*str - '0');
		else
			return (sign * val);
		str++;
	}
	return (sign * val);
}
