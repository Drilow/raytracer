/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 20:23:50 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 04:11:53 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *l)
{
	while (l != NULL)
	{
		if (l->content != NULL)
			ft_putstr((char *)l->content);
		l = l->next;
	}
}
