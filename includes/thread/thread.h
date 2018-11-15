/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:01:17 by adleau            #+#    #+#             */
/*   Updated: 2018/11/15 20:00:52 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include <pthread.h>
# define RT_THREADS_NB 8
# define THREADS_NB RT_THREADS_NB
# define OBJ_THREADS_NB 8
# include <objects/object.h>
# include <raytracing/collision.h>

enum state
{
					STATE_A,
					STATE_B
};

typedef struct		s_thread
{
	void			*data;
	int				th_index;
    t_ray           ray;
    t_poly_obj      *po;
    t_collision     *col;
}					t_thread;

#endif
