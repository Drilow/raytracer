/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:27:09 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/16 13:08:26 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof_ispow(const char *str, double res, double neg)
{
	if (*str == '-')
		return (res * neg * ft_powe((double)ft_atoi(++str)));
	return (res * neg * ft_powe((double)ft_atoi(++str)));
}

double	ft_atof(const char *str)
{
	double	neg;
	double	fact;
	double	res;

	res = 0.0;
	neg = 1.0;
	fact = 1.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		neg = (*str++ == '-') ? -1 : 1;
	while (ft_isdigit(*str))
		res = res * 10.0 + (double)(*str++ - '0');
	if (*str == '.')
	{
		while (ft_isdigit(*++str) && (fact /= 10))
		{
			res += fact * (double)(*str - '0');
			if ((*str + 1) == 'E' || *str + 1 == 'e')
				res += fact * (double)*str - '0';
		}
	}
	if (*str == 'E' || *str == 'e')
		return (ft_atof_ispow(str, res, neg));
	return (res * neg);
}
