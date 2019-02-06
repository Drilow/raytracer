/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:51:22 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 16:09:57 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H
# include <math.h>
# define PI M_PI
# define FOV (PI / 3)

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_dpoint
{
	double			x;
	double			y;
}					t_dpoint;

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	trans;
}					t_rgb;

typedef struct		s_rpoint
{
	double			x;
	double			y;
	double			z;
}					t_rpoint;

typedef struct		s_ray
{
	t_rpoint		p;
	t_rpoint		vector;
}					t_ray;

t_ray				get_ray(t_rpoint p, t_rpoint vector);
t_rpoint			closer(t_rpoint p, t_rpoint a, t_rpoint b);
t_rpoint			new_point(t_rpoint start, t_rpoint vector, double factor);
t_rpoint			set_rpoint(double x, double y, double z);
t_rpoint			get_vector(t_rpoint a, t_rpoint b);
t_rpoint			cross_product(t_rpoint v1, t_rpoint v2);
double				scalar(t_rpoint v1, t_rpoint v2);
double				vlength(t_rpoint v);
t_rpoint			vnorm(t_rpoint v);
t_rpoint			vnorm_to_length(t_rpoint v, double len);
double				vangle(t_rpoint v1, t_rpoint v2);
double				ft_delta(t_point a, t_point b);
int					ft_deltasq(t_point a, t_point b);
double				deltasq(t_rpoint a, t_rpoint b);
double				point_to_line_distance(t_rpoint p, t_rpoint line_p,
t_rpoint line_v);
#endif
