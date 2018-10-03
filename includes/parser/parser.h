/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:18:29 by adleau            #+#    #+#             */
/*   Updated: 2018/10/03 17:03:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <objects/object.h>
# include <extra/extra_defs.h>
# include <stdbool.h>

bool			parse(char *file);
bool			cmp_chars(char *s, char *o, int start);
bool			get_next_nb(char *s, int *index, double *nb1, unsigned char *nb2);
bool			get_next_rpoint(char *s, t_rpoint *p, int *index);
bool			get_obj_core(char *s, t_obj *obj, int *index, t_rgb *clr);
bool			get_obj(char *s, void *o, int *index, int type);
void			set_obj(t_obj *o);
bool			get_cube(char *s, t_obj *c, int *index);
bool			get_tetrahedron(char *s, t_obj *t, int *index);
bool			set_cube(t_rpoint position, double size, t_obj *c);
bool			set_tetrahedron(t_rpoint position, double size, t_obj *t);
bool			validate_obj(t_rpoint pos, double size, char *path, t_obj *o);

#endif
