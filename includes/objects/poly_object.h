/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_object.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:47:24 by adleau            #+#    #+#             */
/*   Updated: 2018/11/30 17:50:39 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLY_OBJECT_H
# define POLY_OBJECT_H

/*
typedef struct		s_face
{
	t_rpoint		p1;
	t_rpoint		p2;
	t_rpoint		p3;
}					t_face;
*/

typedef struct		s_vertex
{
	t_rpoint		p;
	t_plane         pl;
  struct s_vertex	*next;
}					t_vertex;

typedef struct		s_poly_obj
{
	double				max_d;
	t_vertex			*vertices;
	struct s_poly_obj	*next;
}					t_poly_obj;

t_poly_obj		*parse_obj(char *scene_line, double size);

#endif
