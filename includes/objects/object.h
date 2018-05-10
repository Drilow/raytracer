/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:08:00 by adleau            #+#    #+#             */
/*   Updated: 2018/05/10 10:56:08 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include <geometry/geometry.h>
# include <stddef.h>
# include <objects/sphere.h>
# include <objects/camera.h>
# include <objects/cone.h>
# include <objects/cylinder.h>
# include <objects/optics.h>
# include <objects/plane.h>
# include <objects/poly_object.h>


typedef struct		s_obj
{
	int				type;
	t_rpoint		position;
	void			*obj;
	t_rgb			color;
	struct s_obj	*next;
}					t_obj;

void			set_obj(t_obj *o);

#endif
