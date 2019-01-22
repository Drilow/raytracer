/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:03:48 by adleau            #+#    #+#             */
/*   Updated: 2019/01/22 11:32:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H
# include <geometry/geometry.h>
# include <rt.h>
#include <stdbool.h>

# define BRIGHTNESS 0.065
# define SHINING_FACTOR 9
# define LIGHT_LOSS false
# define LIGHT_DISTANCE_FACTOR 2000

typedef struct			s_collision
{
	t_rpoint			p;
	t_rpoint			normal;
	t_obj				*o;
	struct s_collision	*next;
	struct s_collision	*reflected;
}						t_collision;

bool				find_collisions(t_rpoint factors, t_dpoint *solutions, double minimum);
bool				poly_obj_collision(t_ray ray, t_poly_obj *po, \
									   t_collision *col);
bool				collision(t_ray ray, t_collision *c);
t_rpoint			normal_collision_vector(t_collision c);
t_collision			*ray_tracing(t_rt *r, t_ray ray, int r_index);
void				free_collisions(t_collision *c);
void				clean_collision_list(t_collision *c);
t_rpoint			reflected_vector(t_rpoint v, t_rpoint normal);
void				reflexion(t_rt *r, t_ray ray, t_collision *c, int index);
t_collision			*add_collision(t_ray ray, t_collision *c, t_collision *tmpc);
t_rpoint			color_to_add(t_rpoint oclr, t_rgb lclr, double af);
t_rpoint			get_color(t_rt *r, t_collision c);
t_rgb				get_ray_color(t_rt *r, t_collision *c);
#endif
