/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_object.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:00:13 by adleau            #+#    #+#             */
/*   Updated: 2018/10/24 17:00:29 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLY_OBJECT_H
# define POLY_OBJECT_H
# include <objects/object.h>

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

t_poly_obj		*parse_obj(char *scene_line);

#endif

