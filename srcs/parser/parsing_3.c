/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 20:51:38 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/05 15:51:45 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool			poly_obj(char *s, t_obj *o)
{
	o->obj = parse_obj(s, o->size);
	if (o->obj == NULL)
		ft_putendl("((t_obj *)new)->obj == NULL\n");
	set_obj(o);
	return (true);
}
