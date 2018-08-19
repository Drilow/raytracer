/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 17:36:47 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
//# include <gl_handling/gl_includes.h>
# include <sdl_stuff/sdl_mgr.h>
# include <scene/scene_list.h>
# include <rt.h>
# include <geometry/geometry.h>
# include <stdbool.h>

# define ANTIALIASING 1
# define AA_ITERATIONS 4
# define AA_LOWER_THRESHOLD 0.9
# define AA_UPPER_THRESHOLD 0.1
# define AA_MIX_RATIO 0.8

typedef struct			s_global
{
	t_scene_list		scene_list;
  //	t_gl_mgr			gl_mgr;
	t_sdl_wrapper		sdl_mgr;
	char				running;
	t_rt				r;
	int					drawn;
}						t_global;

void					usage(char *s, int i);
void					ft_exit(char *msg_error, int i);

#endif
