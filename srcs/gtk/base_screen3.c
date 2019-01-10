/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:52 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 17:40:52 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>

extern t_global		g_global;

void			free_poly(t_poly_obj *p)
{
	t_poly_obj	*tmp;
	t_poly_obj	*freed_o;
	t_vertex	*tmp_v;
	t_vertex	*freed_v;

	tmp = p;
	while (tmp)
	{
		tmp_v = tmp->vertices;
		while (tmp_v)
		{
			freed_v = tmp_v;
			tmp_v = tmp_v->next;
			free(freed_v);
			freed_v = NULL;
		}
		freed_o = tmp;
		tmp = tmp->next;
		free(freed_o);
		freed_o = NULL;
	}
}

void			free_objects(t_obj *start)
{
	t_obj		*tmp;
	t_obj		*swap;

	tmp = start;
	while (tmp)
	{
		swap = tmp;
		if (swap->type % 10 == 6)
			free_poly(((t_poly_obj*)swap->obj));
		tmp = tmp->next;
		free(swap);
		swap = NULL;
	}
}
