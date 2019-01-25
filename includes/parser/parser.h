/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:18:29 by adleau            #+#    #+#             */
/*   Updated: 2019/01/25 15:33:37 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <objects/object.h>
# include "../Libjson/includes/json.h"
# include <extra/extra_defs.h>
# include <stdbool.h>

typedef	struct		s_checkplane
{
	bool			(*f)(t_obj *o, t_json_value *val);
	int				i;
}					t_checkplane;

typedef	struct		s_checkcyl
{
	bool			(*f)(t_obj *o, t_json_value *val);
	int				i;
}					t_checkcyl;

typedef	struct		s_checkcone
{
	bool			(*f)(t_obj *o, t_json_value *val);
	int				i;
}					t_checkcone;

typedef struct		s_check_obj
{
	bool			(*f)(t_json_object *obj);
	unsigned long	i;
}					t_check_obj;

bool				parse(char *file);
bool				get_started(t_json_value *val);
bool				start_parse(t_json_object *obj, int type, unsigned long nb);
bool				cmp_chars(char *s, char *o, int start);
bool				get_next_nb(char *s, int *index, double *nb1,
unsigned char *nb2);
bool				get_next_rpoint(char *s, t_rpoint *p, int *index);
void				set_obj(t_obj *o);
bool				get_cube(t_obj *c, double size);
bool				get_tetrad(t_obj *t, double size);
bool				set_cube(t_rpoint position, double size, t_obj *c);
bool				set_tetrahedron(t_rpoint position, double size, t_obj *t);
bool				validate_obj(t_rpoint pos, double size, char *path,
t_obj *o);
void				put_inf_to_glob(t_obj *obj);
void				parse_camera(t_json_object *obj, unsigned long nb);
void				*parse_amblight(t_json_object *obj, unsigned long nb);
void				parse_light(t_json_object *obj, unsigned long nb);
t_rgb				get_obj_color(t_json_value *val);
bool				parse_object(t_json_object *obj, unsigned long nb);
bool				get_plane_inf(t_json_object *obj);
bool				get_sphere_inf(t_json_object *obj);
t_obj				*malloc_object(int type);
t_obj				*malloc_object2(int type);
bool				get_cone_inf(t_json_object *obj);
bool				get_cyl_inf(t_json_object *obj);
bool				prerotate(t_obj *obj, t_json_value *val, int type);
void				rotate_obj(void *o, int type, t_rpoint angle);
bool				get_poly_objinf(t_json_object *obj);
bool				poly_obj(char *s, t_obj *o);
bool				get_cube_inf(t_json_object *obj);
bool				get_tetra_inf(t_json_object *obj);
bool				check_arr(t_json_array *arr);
bool				verif_infinite(t_obj *o, t_json_value *val);
bool				get_inf(t_obj *o, t_json_value *val);
bool				get_pyra_inf(t_json_object *obj);
bool				add_vertex(t_vertex **v_list, char *line, double size);
bool				parse_face(t_poly_obj *face, char *line, t_vertex *v_list);
void				free_vlist(t_vertex **v_list);
bool				get_next_double(char *line, int *index, double *a);
t_poly_obj			*pmalloc_po(void);
t_vertex			*pmalloc_vertex(void);
bool				get_pyramid(t_obj *p, double base_size, double height);
void				get_dodecahedron_vertices(t_rpoint *p, double size);
void				get_dodecahedron_faces(t_rpoint *v, t_rpoint **faces);
bool				get_dodecahedron(t_obj *d, double size);
bool				get_dod_inf(t_json_object *obj);
bool				geet_reflex(t_json_value *val, t_obj *o);

#endif
