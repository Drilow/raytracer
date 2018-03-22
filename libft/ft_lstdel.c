/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:42:22 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:44:37 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	while ((*alst) != NULL)
	{
		tmp = (*alst)->next;
		(*del)((*alst)->content, (*alst)->content_size);
		free((*alst));
		(*alst) = tmp;
	}
	free(tmp);
	alst = NULL;
	tmp = NULL;
}
