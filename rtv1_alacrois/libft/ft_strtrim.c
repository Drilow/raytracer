/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:17:38 by alacrois          #+#    #+#             */
/*   Updated: 2014/12/03 17:44:33 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_trimstart(char const *s)
{
	int		i;

	i = 0;
	while ((s[i] == ' ') || (s[i] == '\n') || (s[i] == '\t'))
		i++;
	if (s[i] == '\0')
		return (0);
	return (i);
}

static int		ft_trimend(char const *s)
{
	int		i;

	i = ft_strlen(s) - 1;
	while (((s[i] == ' ') || (s[i] == '\n') || (s[i] == '\t')) && (i > -1))
		i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*trim_s;
	int		i;
	int		i2;

	if (s == NULL)
		return (NULL);
	trim_s = (char *)malloc(sizeof(*trim_s) * (ft_trimend(s) - \
		ft_trimstart(s) + 2));
	if (trim_s == NULL)
		return (NULL);
	i = ft_trimstart(s);
	i2 = 0;
	while (i <= ft_trimend(s))
	{
		trim_s[i2] = s[i];
		i++;
		i2++;
	}
	trim_s[i2] = '\0';
	return (trim_s);
}
