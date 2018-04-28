/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:46:29 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 19:28:45 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPTICS_H
# define	OPTICS_H
# include <objects/object.h>
# include <geometry/geometry.h>
# include <stdbool.h>

typedef struct		s_light_clr
{
	t_rpoint		clr;
	double			shining;
}					t_light_clr;

typedef struct		s_light
{
	t_rpoint		source;
	t_rgb			color;
	struct s_light	*next;
}					t_light;

bool			get_light(char *s, t_light *l, int *index);

#endif
