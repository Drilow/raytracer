/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:04:46 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/05 15:51:36 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <extra/extra_defs.h>
#include <libft.h>

bool			get_next_nb(char *s, int *index, double *nb1, \
							unsigned char *nb2)
{
	int			i;

	i = *index;
	while (ft_isdigit(s[i]) == 0 && s[i] != '-' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (false);
	if (nb1 != NULL)
		*nb1 = (double)ft_atoi(s + i);
	else
		*nb2 = (unsigned char)ft_atoi(s + i);
	while (ft_isdigit(s[i]) == 1 || s[i] == '-')
		i++;
	*index = i;
	return (true);
}

bool			get_next_rpoint(char *s, t_rpoint *p, int *index)
{
	if (get_next_nb(s, index, &(p->x), NULL) == true && \
		get_next_nb(s, index, &(p->y), NULL) == true && \
		get_next_nb(s, index, &(p->z), NULL) == true)
		return (true);
	return (false);
}
