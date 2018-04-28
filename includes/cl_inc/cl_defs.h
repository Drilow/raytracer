/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_defs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 13:03:48 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 13:19:45 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_DEFS_H
# define CL_DEFS_H
# include <OpenCL/opencl.h>

// dev = device

typedef struct			s_cl_mgr
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				input;
	cl_mem				output;
}						t_cl_mgr;

#endif
