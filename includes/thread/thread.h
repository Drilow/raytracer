/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:03:48 by adleau            #+#    #+#             */
/*   Updated: 2018/05/10 10:57:51 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include <sdl_stuff/sdl_mgr.h>
# include <pthread.h>
# define RT_THREADS_NB 8
# define THREADS_NB RT_THREADS_NB
# define OBJ_THREADS_NB 8
# include <objects/object.h>
# include <raytracing/collision.h>

typedef struct		s_thread
{
	t_sdl_wrapper	*e;
	void			*data;
	int				th_index;
    t_ray           ray;
    t_poly_obj      *po;
    t_collision     *col;
}					t_thread;
#endif
