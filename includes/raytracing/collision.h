/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:00:44 by adleau            #+#    #+#             */
/*   Updated: 2018/11/17 22:26:23 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H
# include <geometry/geometry.h>
# include <rt.h>
#include <stdbool.h>

# define BRIGHTNESS 0.065
# define SHINING_FACTOR 9
//# define AMBIENT_LIGHT 0.1
# define AMBIENT_LIGHT 12
# define LIGHT_DISTANCE_FACTOR 2000

typedef struct			s_collision
{
	bool				c;
	t_rpoint			p;
	t_rpoint			normal;
	t_obj				*o;
	struct s_collision	*next;
	struct s_collision	*reflected;
}						t_collision;

bool				find_collisions(t_rpoint factors, t_dpoint *solutions);

//bool				sphere_collision(t_ray ray, t_sphere *s, t_rpoint *p);
//bool				plane_collision(t_ray ray, t_plane *pl, t_rpoint *p);
//bool				get_cc_eq_factors(t_ray ray, t_cone *c, t_rpoint *f);
//bool				cone_collision(t_ray ray, t_cone *c, t_rpoint *p);
//t_rpoint			get_cyc_eq_factors(t_ray ray, t_cylinder *c);
//bool				cylinder_collision(t_ray ray, t_cylinder *c, t_rpoint *p);
bool				poly_obj_collision(t_ray ray, t_poly_obj *po, \
									   t_collision *col);
//t_bool				collision(t_ray ray, t_obj *o, t_rpoint *p);
bool				collision(t_ray ray, t_collision *c);
t_rpoint			normal_collision_vector(t_collision c);
t_collision			*ray_tracing(t_rt *r, t_ray ray);
void				free_collisions(t_collision *c);

//t_rgb				get_ray_color(t_rt *r, t_collision c);
t_rgb				get_ray_color(t_rt *r, t_collision *c, bool debug);
#endif
