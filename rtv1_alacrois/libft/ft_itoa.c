/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:26:22 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/27 20:59:06 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int n)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while ((n > 9) || (n < -9))
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_strswap(char *a, char *b)
{
	char	tmp;

	if (a != b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

static void	ft_strrev(char *str)
{
	int		len;
	int		i;

	len = ft_strlen(str) - 1;
	i = -1;
	while (++i <= (len / 2))
		ft_strswap((str + i), (str + len - i));
}

static int	ft_modten(int n)
{
	n = n % 10;
	if (n < 0)
		n = -n;
	return (n);
}

char		*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*nb;

	len = ft_nblen(n);
	i = 0;
	nb = (char *)malloc(sizeof(*nb) * (len + 1));
	if (nb == NULL)
		return (NULL);
	if (n < 0)
		nb[len - 1] = '-';
	nb[len] = '\0';
	while ((n > 9) || (n < -9))
	{
		nb[i] = '0' + ft_modten(n);
		n = n / 10;
		i++;
	}
	nb[i] = '0' + ft_modten(n);
	ft_strrev(nb);
	return (nb);
}
