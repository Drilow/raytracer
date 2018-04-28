/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:51:22 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 17:06:06 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GEOMETRY_H
# define	GEOMETRY_H
# define PI M_PI
# define FOV (PI / 3)

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		trans;
}						t_rgb;

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

#endif
