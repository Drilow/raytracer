/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:49:50 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:50:00 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct		s_cylinder
{
	t_rpoint		summit;
	t_rpoint		vector;
	double			radius;
	t_bool			infinite;
}					t_cylinder;


#endif
