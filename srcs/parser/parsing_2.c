/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:04:46 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/22 16:15:22 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <extra/extra_defs.h>
#include <parser/parser.h>
#include <libft.h>
#include <geometry/geometry.h>
#include <objects/object.h>
#include <maths/transformations.h>

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
