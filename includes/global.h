/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/10/04 15:21:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# include <gtk_mgr/gtk_mgr.h>
# include <scene/scene_list.h>
# include <rt.h>
# include <geometry/geometry.h>
# include <stdbool.h>
# include <gtk/gtk.h>
# define ANTIALIASING 1
# define AA_ITERATIONS 4
# define AA_LOWER_THRESHOLD 0.9
# define AA_UPPER_THRESHOLD 0.1
# define AA_MIX_RATIO 0.8

typedef struct				s_base_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*open_button;
	GtkWidget				*exit_button;
}							t_base_view;

typedef struct			s_global
{
	t_base_view			base_view;
	char				running;
	t_rt				*r;
	t_rt				*first_scene;
	int					drawn;
}						t_global;

void					usage(char *s, int i);
void					ft_exit(char *msg_error, int i);
void					init_gtk(int ac, char **av);
void					main_screen(GtkApplication *app, gpointer user_data);
void					validate_sphere(t_sphere *s);
void					validate_plane(t_plane *p);
void					validate_cone(t_cone *c);
void					validate_cylinder(t_cylinder *c);
void					edit_sphere_view(t_sphere *s);
void					edit_plane_view(t_plane *p);
void					edit_cone_view(t_cone *c);
void					edit_cylinder_view(t_cylinder *c);

#endif
