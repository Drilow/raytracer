/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:22:24 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:28:37 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_MGR_H
# define SDL_MGR_H
# define WIN_H 300
# define WIN_W 300
# include <SDL.h>
# include <SDL_image.h>

typedef struct			s_sdl_wrapper
{
	SDL_Window			*screen;
	SDL_Surface			*surf;
	SDL_Renderer		*renderer;
	SDL_Texture			*tex;
	SDL_Event			event;
}						t_sdl_wrapper;

void					init_sdl_wrap(t_sdl_wrapper *wrap);

#endif
