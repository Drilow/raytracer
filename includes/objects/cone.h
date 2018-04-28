/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:49:23 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:49:28 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CONE_H
# define	CONE_H

typedef struct		s_cone
{
	t_rpoint		summit;
	t_rpoint		vector;
	double			angle;
	t_bool			infinite;
}					t_cone;

#endif
