/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 23:15:25 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/29 20:36:28 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*element;

	new_lst = ft_lstcpyone(f(lst));
	if (new_lst == NULL)
		return (NULL);
	element = new_lst;
	lst = lst->next;
	while (lst != NULL)
	{
		element->next = ft_lstcpyone(f(lst));
		element = element->next;
		lst = lst->next;
		if (element == NULL)
			return (NULL);
	}
	return (new_lst);
}
