/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 15:38:35 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/22 15:39:46 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strins_free(char *src, char *addon, int index)
{
	char	*s;

	s = ft_strins(src, addon, index);
	if (addon != NULL)
		free(addon);
	return (s);
}
