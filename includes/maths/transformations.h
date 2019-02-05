/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 19:29:36 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 16:10:01 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H
# include <geometry/geometry.h>
# include <stdbool.h>

void			rotate_obj(void *o, int type, t_rpoint angle);
void			translate_obj(void *o, int type, t_rpoint translation);
void			rotate(t_rpoint *p, t_rpoint angle);
bool			ft_solve_equation(t_rpoint factors, t_dpoint *result);

#endif
