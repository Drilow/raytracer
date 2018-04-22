/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdupone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 19:33:01 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/29 19:35:58 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdupone(t_list *src)
{
	t_list	*new;

	if (src == NULL)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = ft_memalloc(src->content_size);
	new->content = ft_memcpy(new->content, src->content, src->content_size);
	new->content_size = src->content_size;
	new->next = src->next;
	return (new);
}
