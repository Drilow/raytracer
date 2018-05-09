/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:09:05 by alacrois          #+#    #+#             */
/*   Updated: 2018/05/09 21:47:37 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <pthread.h>

# define WIN_SIZE_X 400
# define WIN_SIZE_Y 250
# define WIN_TITLE "rtv1"
# define RT_THREADS_NB 8
# define THREADS_NB RT_THREADS_NB
# define OBJ_THREADS_NB 8
# define PI M_PI
# define FOV (PI / 3)
# define BRIGHTNESS 0.065
//# define SHINING_FACTOR 0.75
# define SHINING_FACTOR 9
//# define AMBIENT_LIGHT 0.1
# define AMBIENT_LIGHT 0
# define LIGHT_DISTANCE_FACTOR 2000

typedef struct		s_ray
{
	t_rpoint		p;
	t_rpoint		vector;
}					t_ray;

typedef struct		s_sphere
{
	t_rpoint		center;
	double			radius;
}					t_sphere;

typedef struct		s_cylinder
{
	t_rpoint		summit;
	t_rpoint		vector;
	double			radius;
	t_bool			infinite;
}					t_cylinder;

typedef struct		s_cone
{
	t_rpoint		summit;
	t_rpoint		vector;
	double			angle;
	t_bool			infinite;
}					t_cone;

typedef struct		s_plane
{
	t_rpoint		vector;
	t_rpoint		p;
}					t_plane;

typedef struct		s_face
{
	t_rpoint		p1;
	t_rpoint		p2;
	t_rpoint		p3;
}					t_face;

typedef struct		s_vertex
{
  t_rpoint			p;
	t_plane			pl;
	struct s_vertex	*next;
}					t_vertex;

typedef struct		s_poly_obj
{
	double					max_d;
  t_vertex					*vertices;
	struct s_poly_obj		*next;
}					t_poly_obj;

typedef struct		s_obj
{
	int				type;
	t_rpoint		position;
	void			*obj;
	t_rgb			color;
	struct s_obj	*next;
}					t_obj;

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

typedef struct		s_rtv1
{
	t_rpoint		cam_position;
	double			screen_distance;
	t_ray			rays[WIN_SIZE_Y][WIN_SIZE_X];
	t_obj			*objects;
	t_light			*lights;
}					t_rtv1;

typedef struct		s_collision
{
	t_bool			c;
	t_rpoint		p;
	t_rpoint		normal;
	t_obj			*o;
}					t_collision;

typedef struct      s_thread
{
    t_env           *e;
//  void            *data;
    int             th_index;
    t_ray           ray;
    t_poly_obj      *po;
    t_collision     *col;
}                   t_thread;

t_bool				set_camera(t_rtv1 *r, char *line);

t_bool				find_collisions(t_rpoint factors, t_dpoint *solutions);

t_bool				sphere_collision(t_ray ray, t_sphere *s, t_rpoint *p);
t_bool				plane_collision(t_ray ray, t_plane *pl, t_rpoint *p);
t_bool				get_cc_eq_factors(t_ray ray, t_cone *c, t_rpoint *f);
t_bool				cone_collision(t_ray ray, t_cone *c, t_rpoint *p);
t_rpoint			get_cyc_eq_factors(t_ray ray, t_cylinder *c);
t_bool				cylinder_collision(t_ray ray, t_cylinder *c, t_rpoint *p);
t_bool				poly_obj_collision(t_ray ray, t_poly_obj *po, \
					t_collision *col);
//t_bool				collision(t_ray ray, t_obj *o, t_rpoint *p);
t_bool				collision(t_ray ray, t_collision *c);
t_collision			ray_tracing(t_rtv1 *r, t_ray ray);

int					expose_hook(t_env *e);
int					key_hook(int keycode, t_env *e);
int					loop_hook(t_env *e);
void				draw_image(t_env *e);

t_bool				get_sphere(char *s, t_sphere *sph, int *index);
t_bool				get_plane(char *s, t_plane *pl, int *index);
t_bool				get_cone(char *s, t_cone *c, int *index);
t_bool				get_cylinder(char *s, t_cylinder *c, int *index);
t_bool				get_light(char *s, t_light *l, int *index);
t_bool				get_obj(char *s, void *o, int *index, int type);
t_bool				parse(t_rtv1 *r, char *file);
t_poly_obj			*parse_obj(char *scene_line);
void				set_obj(t_obj *o);
void				usage(char *s);

t_bool				get_next_rpoint(char *s, t_rpoint *p, int *index);
t_bool				get_next_nb(char *s, int *index, double *nb1, \
					unsigned char *nb2);
t_ray				get_ray(t_rpoint p, t_rpoint vector);
t_rpoint			get_vector(t_rpoint a, t_rpoint b);
double				scalar(t_rpoint v1, t_rpoint v2);
t_rpoint			new_point(t_rpoint start, t_rpoint vector, double factor);
t_rpoint			set_rpoint(double x, double y, double z);
double				vlength(t_rpoint v);
t_rpoint			vnorm(t_rpoint v);
t_rpoint			vnorm_to_length(t_rpoint v, double len);
double				vangle(t_rpoint v1, t_rpoint v2);
t_rpoint			cross_product(t_rpoint v1, t_rpoint v2);
double				point_to_line_distance(t_rpoint p, t_rpoint line_p, \
					t_rpoint line_v);
t_rpoint			closer(t_rpoint p, t_rpoint a, t_rpoint b);
double				deltasq(t_rpoint a, t_rpoint b);
void				rotate(t_rpoint *p, t_rpoint angle);
void				rotate_obj(void *o, int type, t_rpoint angle);
void				translate_obj(void *o, int type, t_rpoint translation);

t_bool				cmp_chars(char *s, char *o, int start);

//t_rpoint			normal_collision_vector(t_obj *o, t_rpoint p);
t_rpoint			normal_collision_vector(t_collision c);
//t_rgb				get_ray_color(t_rtv1 *r, t_obj *o, t_rpoint p);
t_rgb				get_ray_color(t_rtv1 *r, t_collision c);
#endif
