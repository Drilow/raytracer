/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:08:00 by adleau            #+#    #+#             */
/*   Updated: 2019/01/29 17:31:26 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include <geometry/geometry.h>
# include <stddef.h>
# include <stdbool.h>
# include <objects/camera.h>
# include <objects/optics.h>

typedef struct			s_obj
{
	bool				enabled;
	int					type;
	t_rpoint			position;
	void				*obj;
	t_rgb				color;
	unsigned char		reflex;
	double				size;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_sphere
{
	double				radius;
}						t_sphere;

typedef struct			s_cone
{
	t_rpoint			vector;
	double				angle;
	bool				infinite;
}						t_cone;

typedef struct			s_cylinder
{
	t_rpoint			vector;
	double				radius;
	bool				infinite;
}						t_cylinder;

typedef struct			s_plane
{
	t_rpoint			vector;
}						t_plane;

typedef struct			s_vertex
{
	t_rpoint			p;
	t_plane				pl;
	struct s_vertex		*next;
}						t_vertex;

typedef struct			s_poly_obj
{
	double				max_d;
	t_vertex			*vertices;
	t_rpoint			rotation;
	struct s_poly_obj	*next;
}						t_poly_obj;

t_poly_obj				*parse_obj(char *str, double size);
bool					plane_collision(t_ray ray, t_plane *pl, t_rpoint pos,
t_rpoint *p);
t_rpoint				get_cyc_eq_factors(t_ray ray, t_cylinder *c,
t_rpoint pos);
bool					cylinder_collision(t_ray ray, t_obj *c, t_rpoint *p);
bool					get_cc_eq_factors(t_ray ray, t_obj *c, t_rpoint *f);
bool					cone_collision(t_ray ray, t_obj *c, t_rpoint *p);
bool					sphere_collision(t_ray ray, t_obj *s, t_rpoint *p);
void					free_objects(t_obj *start);
void					free_poly(t_poly_obj *p);
void					free_lights(t_light *start);

#endif
