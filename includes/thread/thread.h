/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:03:48 by adleau            #+#    #+#             */
/*   Updated: 2018/11/19 15:25:33 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include <pthread.h>
# define THREADS_NB 8

typedef struct		s_thread
{
	void			*data;
	int				th_index;
}					t_thread;
#endif
