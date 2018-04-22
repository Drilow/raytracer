/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 19:06:08 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/01 19:29:22 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstnadd(t_list **alst, t_list *new, size_t position)
{
	t_list	*elem;
	size_t	index;

	elem = *alst;
	index = 1;
	if (((elem == NULL) && (position != 1)) || (position < 1))
		return ;
	if (position == 1)
	{
		new->next = *alst;
		*alst = new;
		return ;
	}
	while (index < (position - 1))
	{
		elem = elem->next;
		if (elem == NULL)
			return ;
		index++;
	}
	new->next = elem->next;
	elem->next = new;
}
