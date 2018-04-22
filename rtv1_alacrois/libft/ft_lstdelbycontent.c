/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelbycontent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 22:31:51 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 04:08:27 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_initvar(t_list **l, t_list **elem, t_list **prev_elem, \
			int *start)
{
	*elem = *l;
	*prev_elem = *elem;
	*start = 0;
}

void		ft_lstdelbycontent(t_list **l, char *content)
{
	t_list	*elem;
	t_list	*prev_elem;
	t_list	*next_elem;
	int		start;

	ft_initvar(l, &elem, &prev_elem, &start);
	while (elem != NULL)
	{
		next_elem = elem->next;
		if (ft_strcmp((const char *)elem->content, (const char *)content) == 0)
		{
			if (start == 0)
				*l = next_elem;
			prev_elem->next = next_elem;
			free(elem->content);
			free(elem);
			elem = next_elem;
		}
		else
		{
			start = 1;
			prev_elem = elem;
			elem = elem->next;
		}
	}
}
