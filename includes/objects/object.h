/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:08:00 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:56:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include <geometry/geometry.h>
# include <stddef.h>

typedef struct		s_obj
{
	int				type;
	t_rpoint		position;
	void			*obj;
	t_rgb			color;
	struct s_obj	*next;
}					t_obj;

#endif
