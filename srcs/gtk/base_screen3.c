/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:52 by adleau            #+#    #+#             */
/*   Updated: 2019/01/09 12:51:36 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global		g_global;

void			free_poly(t_poly_obj *p)
{
	t_poly_obj	*tmp;
	t_poly_obj	*freed_o;
	t_vertex	*tmp_v;
	t_vertex	*freed_v;

	tmp = p;
	printf("PPP %p\n", p);
	while (tmp)
	{
		tmp_v = p->vertices;
		while (tmp_v)
		{
			printf("aha\n");
			freed_v = tmp_v;
			printf("aha %p\n", tmp_v->next);
			tmp_v = tmp_v->next;
			printf("aha\n");
			free(freed_v);
			printf("aha\n");
			freed_v = NULL;
			printf("aha\n");
		}
		freed_o = tmp;
		tmp = tmp->next;
		printf("OH! %p\n", freed_o);
		free(freed_o);
		freed_o = NULL;
	}
}

void			destroy_scene(void)
{
	t_obj			*to_free;
	t_obj			*tmp;

	to_free = g_global.r->objects;
	while (to_free)
	{
		tmp = to_free->next;
		if (to_free->type == 6)
			free_poly((t_poly_obj*)to_free->obj);
		else if (to_free->obj)
		{
			free(to_free->obj);
			to_free->obj = NULL;
		}
		if (to_free)
		{
			free(to_free);
			to_free = NULL;
		}
	}
}
