/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 19:56:31 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/01 20:04:24 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *elem1, t_list *elem2)
{
	void	*content_tmp;
	size_t	content_size_tmp;

	if (elem1 == NULL || elem2 == NULL || elem1 == elem2)
		return ;
	content_tmp = elem1->content;
	content_size_tmp = elem1->content_size;
	elem1->content = elem2->content;
	elem1->content_size = elem2->content_size;
	elem2->content = content_tmp;
	elem2->content_size = content_size_tmp;
}
