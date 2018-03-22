/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:42:45 by adleau            #+#    #+#             */
/*   Updated: 2017/11/07 09:44:25 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*tmpret;
	t_list	*tmplst;

	if (lst == NULL || f == NULL)
		return (NULL);
	tmplst = f(lst);
	if ((ret = ft_lstnew(tmplst->content, tmplst->content_size)))
	{
		tmpret = ret;
		lst = lst->next;
		while (lst != NULL)
		{
			tmplst = (*f)(lst);
			if (!(tmpret->next = ft_lstnew(tmplst->content,
					tmplst->content_size)))
				return (NULL);
			tmpret = tmpret->next;
			lst = lst->next;
		}
	}
	return (ret);
}
