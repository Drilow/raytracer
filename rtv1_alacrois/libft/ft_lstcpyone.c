/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpyone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 19:26:00 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/29 19:28:23 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpyone(t_list *src)
{
	t_list	*new;

	if (src == NULL)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = ft_memalloc(src->content_size);
	new->content = src->content;
	new->content_size = src->content_size;
	new->next = src->next;
	return (new);
}
