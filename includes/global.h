/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/05/10 09:20:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# include <sdl_stuff/sdl_mgr.h>
# include <scene/scene_list.h>
# include <rt.h>
# include <geometry/geometry.h>
# include <stdbool.h>

typedef struct			s_global
{
	t_scene_list		scene_list;
	t_sdl_wrapper		sdl_mgr;
	char				running;
	t_rt				r;
	int					drawn;
}						t_global;

void					usage(char *s, int i);
void					ft_exit(char *msg_error, int i);
void					init_glfw(void);
void					error_callback(int error, const char* description);
void					destroy_glfw(void);
void					draw(void);


#endif
