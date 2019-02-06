/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:06:31 by adleau            #+#    #+#             */
/*   Updated: 2019/01/22 21:33:47 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include <libft.h>
# include <geometry/geometry.h>

void			draw_image(void);
t_rgb			two_colors_average(t_rgb a, t_rgb b, double ratio);
double			colorcmp(t_rgb a, t_rgb b);
void			free_pixdup(t_rgb **pixdup);
void			free_aa(int **aa);
t_rgb			get_pixel(unsigned char *buf, int x, int y);
void			apply_aa(t_point p, t_rgb **pixdup);
void			antialiasing(void);
#endif
