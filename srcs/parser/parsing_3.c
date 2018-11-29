/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 20:51:38 by alacrois          #+#    #+#             */
/*   Updated: 2018/11/29 10:43:34 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <extra/extra_defs.h>
#include <parser/parser.h>
#include <libft.h>

bool			cmp_chars(char *s, char *o, int start)
{
	int			is;
	int			io;

	is = start - 1;
	io = -1;
	while (o[++io] != '\0')
	{
		if (s[++is] != o[io])
			return (false);
	}
	return (true);
}

bool			get_poly_obj(char *s, t_obj *o)
{
	o->obj = parse_obj(s);
	if (o->obj == NULL)
		ft_putendl("((t_obj *)new)->obj == NULL\n");
	set_obj(o);
	return (true);
}
