/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:25:15 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:29:14 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sdl_stuff/sdl_mgr.h>
#include <libft.h>

void			init_sdl_wrap(t_sdl_wrapper *wrap)
{
	int			flags;
	int			initted;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_putendl_fd("Failed to init SDL", 2);
	wrap->screen = NULL;
	flags = IMG_INIT_PNG;
	initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		ft_putendl_fd
("IMG_Init: Failed to init required jpg and png support!\n", 2);
		exit(1);
	}
	if (!(wrap->screen = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)))
		exit(1);
	if (!(wrap->surf = SDL_CreateRGBSurfaceWithFormat(0, WIN_W, WIN_H, 32,
SDL_PIXELFORMAT_RGBA32)))
		exit(1);
	wrap->renderer = NULL;
	wrap->tex = NULL;
}
