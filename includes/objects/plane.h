/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:48:46 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 17:01:34 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include <stdbool.h>
# include <objects/object.h>

typedef struct		s_plane
{
	t_rpoint		vector;
	t_rpoint		p;
}					t_plane;

bool				get_plane(char *s, t_obj *o, int *index);
bool				plane_collision(t_ray ray, t_plane *pl, t_rpoint *p);
#endif
