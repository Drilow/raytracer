/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   po_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 10:27:07 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:52:03 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>

t_poly_obj		*malloc_po(void)
{
	t_poly_obj	*obj;

	obj = NULL;
	if (!(obj = (t_poly_obj *)malloc(sizeof(t_poly_obj))))
		ft_exit("Malloc error ('po_malloc.c' --> Ln 25)", 1);
	obj->next = NULL;
	return (obj);
}

t_vertex		*malloc_vertex(void)
{
	t_vertex	*v;

	v = NULL;
	if (!(v = (t_vertex *)malloc(sizeof(t_vertex))))
		ft_exit("Malloc error ('po_malloc.c' --> Ln 36)", 1);
	v->next = NULL;
	return (v);
}

t_poly_obj		*pmalloc_po(void)
{
	t_poly_obj	*obj;

	if (!(obj = (t_poly_obj *)malloc(sizeof(t_poly_obj))))
		ft_exit("Malloc error ('po_malloc.c' --> Ln 46)", 1);
	obj->next = NULL;
	return (obj);
}

t_vertex		*pmalloc_vertex(void)
{
	t_vertex	*v;

	if (!(v = (t_vertex *)malloc(sizeof(t_vertex))))
		ft_exit("Malloc error ('po_malloc.c' --> Ln 56)", 1);
	v->next = NULL;
	return (v);
}
