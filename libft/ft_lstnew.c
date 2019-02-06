/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:42:56 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:44:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_lnk;

	new_lnk = NULL;
	if ((new_lnk = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		new_lnk->content = NULL;
		new_lnk->content_size = 0;
		new_lnk->next = NULL;
		return (new_lnk);
	}
	if ((new_lnk->content = (void*)malloc(sizeof(void) * content_size))
	== NULL)
		return (NULL);
	new_lnk->content = ft_memcpy(new_lnk->content, content, content_size);
	new_lnk->content_size = content_size;
	new_lnk->next = NULL;
	return (new_lnk);
}
