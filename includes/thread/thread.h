/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:03:48 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 22:10:34 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include <sdl_stuff/sdl_mgr.h>
# include <pthread.h>
# define THREADS_NB 8


typedef struct		s_thread
{
	t_sdl_wrapper			*e;
	void			*data;
	int				th_index;
}					t_thread;
#endif
