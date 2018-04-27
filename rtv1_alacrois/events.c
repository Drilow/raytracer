/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 04:36:47 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/27 16:26:44 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->i->img_p, 0, 0);
	return (0);
}

int				key_hook(int keycode, t_env *e)
{
	if (keycode == 53 && e != NULL)
		exit(0);
	return (0);
}
