/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_mgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 21:18:21 by adleau            #+#    #+#             */
/*   Updated: 2018/08/07 12:50:35 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTK_MGR_H
# define GTK_MGR_H
# include <gtk/gtk.h>
# define UI_FILE "uiconfig/rt2.glade"

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

}							t_filter_view;

typedef struct				s_add_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*sphere_button;
	GtkWidget				*cylinder_button;
	GtkWidget				*cone_button;
	GtkWidget				*obj_file_button;
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
	GtkWidget				*scale_x_spin;
	GtkWidget				*scale_y_spin;
	GtkWidget				*scale_z_spin;
	GtkWidget				*ok_button;
	GtkWidget				*cancel_button;
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
	GtkWidget				*edit_button;
	GtkWidget				*edit_img;
	GtkWidget				*export_button;
	GtkWidget				*export_img;
	GtkWidget				*render_area;
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
	unsigned char			*buf;
	t_ui					ui;
}							t_gtk_mgr;

void						init_gtk_variables(void);

#endif
