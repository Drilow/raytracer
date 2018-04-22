/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 18:52:47 by alacrois          #+#    #+#             */
/*   Updated: 2015/05/06 12:05:53 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (alst != NULL)
	{
		elem = *alst;
		if (elem == NULL)
			*alst = new;
		else
		{
			while (elem->next != NULL)
				elem = elem->next;
			elem->next = new;
		}
	}
}
