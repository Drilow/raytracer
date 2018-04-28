/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:49:23 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 20:02:07 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CONE_H
# define	CONE_H
# include <stdbool.h>

typedef struct		s_cone
{
	t_rpoint		summit;
	t_rpoint		vector;
	double			angle;
	bool			infinite;
}					t_cone;

bool			get_cone(char *s, t_cone *c, int *index);
bool			get_cc_eq_factors(t_ray ray, t_cone *c, t_rpoint *f);
#endif
