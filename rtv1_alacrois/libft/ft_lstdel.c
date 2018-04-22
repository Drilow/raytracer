/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 22:53:34 by alacrois          #+#    #+#             */
/*   Updated: 2014/11/29 19:03:20 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*elem;
	t_list	*next_elem;

	elem = *alst;
	while (elem != NULL)
	{
		next_elem = elem->next;
		del(elem->content, elem->content_size);
		free(elem);
		elem = next_elem;
	}
	if (*alst != NULL)
		*alst = NULL;
}
