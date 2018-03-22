/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:41:58 by adleau            #+#    #+#             */
/*   Updated: 2017/08/31 14:41:59 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*test(char *ret, long n, int len, int min_flag)
{
	int		size;
	int		nbr;
	int		tmp;

	size = 1;
	tmp = n;
	while (tmp / 10 > 0)
	{
		size = size * 10;
		tmp = tmp / 10;
	}
	while (size > 0)
	{
		nbr = 0;
		nbr = n / size;
		if (size == 1)
			ret[len] = ('0' + nbr + min_flag);
		else
			ret[len] = ('0' + nbr);
		len += 1;
		n = n % size;
		size = size / 10;
	}
	ret[len] = '\0';
	return (ret);
}

static int	ret_count(int n, int count)
{
	if (n < 0)
		count += 1;
	while (n / 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	int		len;
	int		i;
	int		count;
	int		min_flag;
	char	*ret;

	min_flag = 0;
	i = n;
	count = 0;
	count = ret_count(n, count);
	if ((ret = (char *)malloc(sizeof(*ret) * (count + 1) + 1)) == NULL)
		return (NULL);
	len = 0;
	if (i < 0)
	{
		ret[len] = '-';
		len += 1;
		if (i == -2147483648)
		{
			min_flag = 1;
			i++;
		}
		i = i * -1;
	}
	return (test(ret, i, len, min_flag));
}
