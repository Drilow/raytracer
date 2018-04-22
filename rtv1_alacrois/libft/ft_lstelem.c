/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstelem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 19:47:29 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/01 19:55:53 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstelem(t_list *lst, size_t position)
{
	t_list	*elem;
	size_t	i;

	elem = lst;
	i = 1;
	while ((i < position) && (elem != NULL))
	{
		elem = elem->next;
		i++;
	}
	if (position < 1)
		return (NULL);
	return (elem);
}
