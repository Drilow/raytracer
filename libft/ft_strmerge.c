/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:57:01 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/15 11:48:58 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmerge(char *src, char *dest, size_t i, size_t j)
{
	char	*ret;

	ret = ft_strjoini(dest, src, j, i);
	ft_strdel(&dest);
	return (ret);
}
