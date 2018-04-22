/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 19:31:10 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/01 19:46:40 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list *lst)
{
	size_t	i;
	size_t	lstlen;

	i = 1;
	lstlen = ft_lstlen(lst);
	if (lstlen < 2)
		return ;
	while (i <= (lstlen / 2))
	{
		ft_lstswap(ft_lstelem(lst, i), ft_lstelem(lst, (lstlen - i + 1)));
		i++;
	}
}
