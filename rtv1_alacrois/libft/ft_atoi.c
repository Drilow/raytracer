/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 19:45:05 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 19:51:28 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_chartype(char c)
{
	if (ft_isdigit(c) == 1)
		return (1);
	if (c == '+' || c == '-')
		return (2);
	if (c == '\n' || c == '\v' || c == '\t'\
		|| c == '\r' || c == '\f' || c == ' ')
		return (3);
	return (0);
}

static int		ft_firstdigit(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_chartype(str[i]) == 0)
			return (-1);
		if (ft_chartype(str[i]) == 2 && ft_chartype(str[i + 1]) != 1)
			return (-1);
		if (ft_isdigit(str[i]) == 1)
			return (i);
		i++;
	}
	return (-1);
}

int				ft_atoi(const char *str)
{
	int		nb;
	int		sign;
	int		i;

	if (str == NULL)
		return (0);
	nb = 0;
	sign = 1;
	i = ft_firstdigit(str);
	if (i == -1)
		return (0);
	if (i > 0 && str[i - 1] == '-')
		sign = -1;
	while (ft_isdigit(str[i]) == 1)
	{
		nb = nb * 10;
		nb = nb + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}
