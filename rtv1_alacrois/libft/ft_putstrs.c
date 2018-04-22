/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 23:41:40 by alacrois          #+#    #+#             */
/*   Updated: 2015/05/28 23:46:26 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrs(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 == NULL)
		return ;
	ft_putstr(s1);
	if (s2 == NULL)
		return ;
	ft_putstr(s2);
	if (s3 == NULL)
		return ;
	ft_putstr(s3);
	if (s4 == NULL)
		return ;
	ft_putstr(s4);
}
