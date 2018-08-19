/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 14:45:26 by adleau           ###   ########.fr       */
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
# define DATA g_global.sdl_mgr.surf
# define ANTIALIASING 1
# define AA_LOWER_THRESHOLD 0.30
# define AA_UPPER_THRESHOLD 0.70

typedef struct			s_global
{
	t_gtk_mgr			gtk_mgr;
	char				running;
	t_rt				r;
	int					drawn;
}						t_global;

void					usage(char *s, int i);
void					ft_exit(char *msg_error, int i);
void					init_gtk(int ac, char **av);
void					main_screen(GtkApplication *app, gpointer user_data);
#endif
