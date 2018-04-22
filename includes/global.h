/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2018/04/22 16:11:14 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# include <gl_handling/gl_includes.h>
# include <scene/scene_list.h>

typedef struct			s_global
{
	t_scene_list		scene_list;
	t_gl_mgr			gl_mgr;

}						t_global;

#endif
