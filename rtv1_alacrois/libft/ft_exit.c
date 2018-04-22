/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 11:18:46 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 03:08:25 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(char *msg_error)
{
	if (msg_error != NULL)
	{
		ft_putstr(msg_error);
		ft_putstr("\n");
	}
	exit(0);
}
