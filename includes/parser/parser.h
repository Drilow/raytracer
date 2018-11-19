/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:18:29 by adleau            #+#    #+#             */
/*   Updated: 2018/11/19 16:33:36 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <objects/object.h>
# include "../Libjson/includes/json.h"
# include <extra/extra_defs.h>
# include <stdbool.h>

bool			parse(char *file);
bool			start_parse(t_json_object *obj, int type, unsigned long nb);
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
void			put_inf_to_glob(t_obj *obj);
void			parse_camera(t_json_object *obj, unsigned long nb);
void			*parse_amblight(t_json_object *obj, unsigned long nb);
void			parse_light(t_json_object *obj, unsigned long nb);
t_rgb			get_obj_color(t_json_value *val);
bool			parse_object(t_json_object *obj, unsigned long nb);
bool			get_plane_inf(t_json_object *obj);
bool			get_sphere_inf(t_json_object *obj);
t_obj			*malloc_object(int type);
bool			get_cone_inf(t_json_object *obj);
bool			get_cyl_inf(t_json_object *obj);
bool			prerotate(t_obj *obj, t_json_value *val, int type);
void			rotate_obj(void *o, int type, t_rpoint angle);
bool			get_poly_objinf(t_json_object *obj);
bool			get_poly_obj(char *s, t_obj *o);

#endif
