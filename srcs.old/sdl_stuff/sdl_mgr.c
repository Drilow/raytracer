/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:25:15 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 22:50:49 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sdl_stuff/sdl_mgr.h>
#include <libft.h>
#include <global.h>

extern t_global	g_global;

void			sdl_loop_init(void)
{
	if (g_global.sdl_mgr.tex)
	{
		SDL_DestroyTexture(g_global.sdl_mgr.tex);
		g_global.sdl_mgr.tex = NULL;
	}
}

void			sdl_loop_end(void)
{
	if (!(g_global.sdl_mgr.renderer))
		if (!(g_global.sdl_mgr.renderer = SDL_CreateRenderer(g_global.sdl_mgr.screen,
															 -1, SDL_RENDERER_ACCELERATED)))
			exit(1);
	if (!(g_global.sdl_mgr.tex))
		if (!(g_global.sdl_mgr.tex =
			  SDL_CreateTextureFromSurface(g_global.sdl_mgr.renderer, g_global.sdl_mgr.surf)))
			exit(1);
	SDL_RenderClear(g_global.sdl_mgr.renderer);
	SDL_RenderCopy(g_global.sdl_mgr.renderer, g_global.sdl_mgr.tex, NULL, NULL);
	SDL_RenderPresent(g_global.sdl_mgr.renderer);
	SDL_DestroyTexture(g_global.sdl_mgr.tex);
	g_global.sdl_mgr.tex = NULL;
}

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
