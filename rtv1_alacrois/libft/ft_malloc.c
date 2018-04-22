/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:28:26 by alacrois          #+#    #+#             */
/*   Updated: 2018/02/28 18:29:52 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (new == NULL)
		ft_exit("malloc error");
	return (new);
}
