/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fcts_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:46:35 by alacrois          #+#    #+#             */
/*   Updated: 2018/04/28 19:51:56 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <geometry/geometry.h>

t_rpoint		get_vector(t_rpoint a, t_rpoint b)
{
	t_rpoint	v;

	v.x = b.x - a.x;
	v.y = b.y - a.y;
	v.z = b.z - a.z;
	return (v);
}

t_rpoint		cross_product(t_rpoint v1, t_rpoint v2)
{
	t_rpoint	new;

	new.x = (v1.y * v2.z) - (v1.z * v2.y);
	new.y = (v1.z * v2.x) - (v1.x * v2.z);
	new.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (new);
}

double			scalar(t_rpoint v1, t_rpoint v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double			vlength(t_rpoint v)
{
	return (sqrt(deltasq(set_rpoint(0, 0, 0), v)));
}

t_rpoint		vnorm(t_rpoint v)
{
	t_rpoint	new;
	double		vlen;

	vlen = vlength(v);
	new.x = v.x / vlen;
	new.y = v.y / vlen;
	new.z = v.z / vlen;
	return (new);
}
