/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:46:29 by adleau            #+#    #+#             */
/*   Updated: 2018/04/28 16:47:02 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPTICS_H
# define	OPTICS_H

typedef struct		s_light_clr
{
	t_rpoint		clr;
	double			shining;
}					t_light_clr;

typedef struct		s_light
{
	t_rpoint		source;
	t_rgb			color;
	struct s_light	*next;
}					t_light;

#endif
