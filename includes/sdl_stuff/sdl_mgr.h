/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:22:24 by adleau            #+#    #+#             */
/*   Updated: 2018/08/19 17:44:00 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_MGR_H
# define SDL_MGR_H
# define WIN_H 900
# define WIN_W 1600
# include <SDL.h>
# include <SDL_image.h>
# include <geometry/geometry.h>

typedef struct			s_sdl_wrapper
{
	SDL_Window			*screen;
	SDL_Surface			*surf;
	SDL_Renderer		*renderer;
	SDL_Texture			*tex;
	SDL_Event			event;
}						t_sdl_wrapper;

void					init_sdl_wrap(t_sdl_wrapper *wrap);
void					sdl_loop_init(void);
void					sdl_loop_end(void);
void					draw_px(SDL_Surface *surf, int x, int y, t_rgb cols);
#endif
