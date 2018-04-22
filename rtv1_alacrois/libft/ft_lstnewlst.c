/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 19:45:26 by alacrois          #+#    #+#             */
/*   Updated: 2015/05/01 19:11:41 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewlst(void *cont, size_t cont_size, size_t l_size)
{
	size_t	index;
	t_list	*new_lst;
	t_list	*elem;

	index = 1;
	if (l_size > 0)
		new_lst = ft_lstnew((void const *)cont, cont_size);
	else
		return (NULL);
	elem = new_lst;
	while (index < l_size)
	{
		elem->next = ft_lstnew((void const *)cont, cont_size);
		if (elem->next == NULL)
			return (NULL);
		elem = elem->next;
		index++;
	}
	return (new_lst);
}
