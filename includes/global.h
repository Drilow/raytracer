/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:57:38 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# include <gl_handling/gl_includes.h>
# include <sdl_stuff/sdl_mgr.h>
# include <scene/scene_list.h>
# include <rt.h>

typedef struct			s_global
{
	t_scene_list		scene_list;
	t_gl_mgr			gl_mgr;
	t_sdl_wrapper		sdl_mgr;
	char				running;
	t_rt				r;
}						t_global;

#endif
