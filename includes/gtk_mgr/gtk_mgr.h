/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_mgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 21:18:21 by adleau            #+#    #+#             */
/*   Updated: 2018/09/02 20:19:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTK_MGR_H
# define GTK_MGR_H
# include <gtk/gtk.h>
# define UI_FILE "uiconfig/rt2.glade"

struct s_obj;
struct s_rgb;

typedef struct s_rgb		t_rgb;
typedef struct s_obj		t_obj;

typedef struct				s_switcher
{
	t_obj					*o;
	int						type;
}							t_switcher;

typedef struct				s_picker_view
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	GtkFileChooser			*chooser;
}							t_picker_view;

typedef struct				s_export_view
{
	GtkWidget				*dialog;
	GtkFileChooserAction	*action;
	GtkFileChooser			*chooser;
}							t_export_view;

typedef struct				s_filter_view
{
	GtkWidget				*win;
}							t_filter_view;

typedef struct				s_add_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*buttonbox;
	GtkWidget				*sphere_button;
	GtkWidget				*plane_button;
	GtkWidget				*cylinder_button;
	GtkWidget				*cone_button;
	GtkWidget				*obj_file_button;
	GtkWidget				*sphere_img;
	GtkWidget				*plane_img;
	GtkWidget				*cylinder_img;
	GtkWidget				*cone_img;
	GtkWidget				*obj_file_img;
	GtkWidget				*x_label;
	GtkWidget				*y_label;
	GtkWidget				*z_label;
	GtkWidget				*translate_img;
	GtkWidget				*rotate_img;
	GtkWidget				*scale_img;
	GtkWidget				*translate_x_spin;
	GtkWidget				*translate_y_spin;
	GtkWidget				*translate_z_spin;
	GtkWidget				*rotate_x_spin;
	GtkWidget				*rotate_y_spin;
	GtkWidget				*rotate_z_spin;
	GtkWidget				*scale_spin;
	GtkWidget				*vector_x;
	GtkWidget				*vector_y;
	GtkWidget				*vector_z;
	GtkWidget				*vector_img;
	GtkWidget				*inf_img;
	GtkWidget				*infinite;
	GtkWidget				*ok_button;
	GtkWidget				*cancel_button;
	t_switcher				sw;
}							t_add_view;

typedef struct				s_main_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*buttonbox;
	GtkWidget				*add_button;
	GtkWidget				*add_img;
	GtkWidget				*filters_button;
	GtkWidget				*filters_img;
	GtkWidget				*select_button;
	GtkWidget				*select_img;
	GtkWidget				*export_button;
	GtkWidget				*export_img;
	GtkWidget				*render_area;
	GtkWidget				*event_box;
}							t_main_view;

typedef struct				s_base_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*open_button;
	GtkWidget				*new_button;
	GtkWidget				*exit_button;
}							t_base_view;

typedef struct				s_ui
{
	t_base_view				base_view;
	t_main_view				main_view;
	t_add_view				add_view;
	t_filter_view			filter_view;
	t_export_view			export_view;
	t_picker_view			picker_view;
}							t_ui;

typedef struct				s_gtk_mgr
{
	cairo_surface_t			*pixmap;
	struct s_obj			***checker;
	struct s_obj			*selected_obj;
	unsigned char			*buf;
	char					editmode;
	t_ui					ui;
}							t_gtk_mgr;

void						draw_px(unsigned char *buf, int x, int y, t_rgb cols);;
void						init_gtk_variables(void);
void						edit_win(t_obj *o);
#endif
