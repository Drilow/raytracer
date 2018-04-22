/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 16:17:37 by alacrois          #+#    #+#             */
/*   Updated: 2017/12/13 04:16:28 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstsort(t_list *l)
{
	size_t	llen;
	size_t	i;
	t_list	*tmp;

	llen = ft_lstlen(l);
	i = 1;
	if (llen < 2)
		return ;
	while (i < llen)
	{
		tmp = l;
		while (tmp->next != NULL)
		{
			if (ft_strcmp((const char *)tmp->content, \
			(const char *)tmp->next->content) > 0)
				ft_lstswap(tmp, tmp->next);
			tmp = tmp->next;
		}
		i++;
	}
}
