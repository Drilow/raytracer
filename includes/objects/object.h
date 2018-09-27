/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:08:00 by adleau            #+#    #+#             */
/*   Updated: 2018/09/27 13:38:50 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include <geometry/geometry.h>
# include <stddef.h>
# include <stdbool.h>
/*
# include <objects/sphere.h>
# include <objects/camera.h>
# include <objects/cone.h>
# include <objects/cylinder.h>
# include <objects/optics.h>
# include <objects/plane.h>
# include <objects/poly_object.h>
*/
# include <objects/camera.h>
# include <objects/optics.h>

typedef struct		s_obj
{
	int				type;
	t_rpoint		position;
	void			*obj;
	t_rgb			color;
	double			size;
	struct s_obj	*next;
}					t_obj;

typedef struct      s_sphere
{
//    t_rpoint        center;
    double          radius;
}                   t_sphere;

typedef struct      s_cone
{
//    t_rpoint        summit;
    t_rpoint        vector;
    double          angle;
    bool            infinite;
}                   t_cone;

typedef struct      s_cylinder
{
//    t_rpoint        summit;
    t_rpoint        vector;
    double          radius;
    bool            infinite;
}                   t_cylinder;

typedef struct      s_plane
{
    t_rpoint        vector;
//    t_rpoint        p;
}                   t_plane;

typedef struct      s_vertex
{
    t_rpoint        p;
    t_plane         pl;
	struct s_vertex   *next;
}                   t_vertex;

typedef struct      s_poly_obj
{
    double              max_d;
    t_vertex            *vertices;
    struct s_poly_obj   *next;
}                   t_poly_obj;

t_poly_obj			*parse_obj(char *scene_line);

bool				get_plane(char *s, t_obj *o, int *index);
bool				plane_collision(t_ray ray, t_plane *pl, t_rpoint pos, \
					t_rpoint *p);

bool				get_cylinder(char *s, t_obj *o, int *index);
t_rpoint			get_cyc_eq_factors(t_ray ray, t_cylinder *c, t_rpoint pos);
bool                cylinder_collision(t_ray ray, t_obj *c, t_rpoint *p);

bool				get_cone(char *s, t_obj *o, int *index);
bool				get_cc_eq_factors(t_ray ray, t_obj *c, t_rpoint *f);
bool                cone_collision(t_ray ray, t_obj *c, t_rpoint *p);

bool				get_sphere(char *s, t_obj *o, int *index);
bool				sphere_collision(t_ray ray, t_obj *s, t_rpoint *p);

#endif
