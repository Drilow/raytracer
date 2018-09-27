/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/09/27 13:07:19 by adleau           ###   ########.fr       */
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
	GtkWidget				*new_button;
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

#endif
