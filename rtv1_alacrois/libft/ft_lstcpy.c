/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 19:30:03 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/29 19:31:41 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *lst_src)
{
	t_list	*new_lst;
	t_list	*elem;

	elem = ft_lstcpyone(lst_src);
	new_lst = elem;
	if (elem == NULL)
		return (NULL);
	while (lst_src != NULL)
	{
		lst_src = lst_src->next;
		elem->next = ft_lstcpyone(lst_src);
		elem = elem->next;
	}
	return (new_lst);
}
