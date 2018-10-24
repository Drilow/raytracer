/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:includes/sdl_stuff/sdl_mgr.h
/*   Created: 2018/04/28 16:22:24 by adleau            #+#    #+#             */
/*   Updated: 2018/05/10 13:29:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_MGR_H
# define SDL_MGR_H
# define WIN_H 250
# define WIN_W 400
# include <SDL.h>
# include <geometry/geometry.h>
=======
/*   Created: 2018/03/27 16:42:16 by alacrois          #+#    #+#             */
/*   Updated: 2018/05/27 16:18:48 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
>>>>>>> merge_result:srcs.old/objects/plane.c

bool			plane_collision(t_ray ray, t_plane *pl, t_rpoint *p)
{
<<<<<<< HEAD:includes/sdl_stuff/sdl_mgr.h
	SDL_Window			*screen;
	SDL_Surface			*surf;
	void				*surf2;
	SDL_Renderer		*renderer;
	SDL_Texture			*tex;
	SDL_Event			event;
}						t_sdl_wrapper;
=======
	t_rpoint	vpl;
	t_rpoint	c;
	t_rpoint	ppl;
	double		tmp;
	double		solution;
>>>>>>> merge_result:srcs.old/objects/plane.c

	vpl = pl->vector;
	c = ray.p;
	ppl = pl->p;
	tmp = scalar(ray.vector, pl->vector);
	if (tmp == 0)
		return (false);
	solution = (scalar(vpl, ppl) - scalar(vpl, c)) / tmp;
	if (solution <= 0)
		return (false);
	*p = new_point(c, ray.vector, solution);
	return (true);
}
