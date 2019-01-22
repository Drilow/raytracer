/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   po_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 10:27:07 by mabessir          #+#    #+#             */
/*   Updated: 2019/01/20 18:57:38 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <objects/object.h>
#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>
#include <parser/parser.h>

t_poly_obj		*malloc_po(void)
{
	t_poly_obj	*obj;

	obj = NULL;
	if (!(obj = (t_poly_obj *)malloc(sizeof(t_poly_obj))))
		exit_properly(1);
	obj->next = NULL;
	return (obj);
}

t_vertex		*malloc_vertex(void)
{
	t_vertex	*v;

	v = NULL;
	if (!(v = (t_vertex *)malloc(sizeof(t_vertex))))
		exit_properly(1);
	v->next = NULL;
	return (v);
}

t_poly_obj		*pmalloc_po(void)
{
	t_poly_obj	*obj;

	if (!(obj = (t_poly_obj *)malloc(sizeof(t_poly_obj))))
		exit_properly(1);
	obj->next = NULL;
	return (obj);
}

t_vertex		*pmalloc_vertex(void)
{
	t_vertex	*v;

	if (!(v = (t_vertex *)malloc(sizeof(t_vertex))))
		exit_properly(1);
	v->next = NULL;
	return (v);
}
