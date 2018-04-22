/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 23:45:40 by alacrois          #+#    #+#             */
/*   Updated: 2017/09/27 23:47:33 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char *s2;

	s2 = ft_strsub(s, start, len);
	free(s);
	return (s2);
}
