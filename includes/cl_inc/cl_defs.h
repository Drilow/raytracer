/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:03:48 by adleau            #+#    #+#             */
/*   Updated: 2018/05/10 12:44:43 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_DEFS_H
# define CL_DEFS_H
# if defined(__APPLE__) || defined(__MACOSX)
# include <OpenCL/opencl.h>
# else
# include <CL/cl.h>
# endif
# include <rt.h>
// dev = device

typedef struct			s_cl_mgr
{
	int					gpu;
	int					cl_err;
	void				*px_arr;
	unsigned int		correct;
	size_t				global_dom;
	size_t				local_dom;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				input;
	cl_mem				output;
}						t_cl_mgr;

#endif







