/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:48:46 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 19:53:17 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include <stdbool.h>

typedef struct		s_plane
{
	t_rpoint		vector;
	t_rpoint		p;
}					t_plane;

bool				get_plane(char *s, t_plane *pl, int *index);
bool				plane_collision(t_ray ray, t_plane *pl, t_rpoint *p);
#endif
