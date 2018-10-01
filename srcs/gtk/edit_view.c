/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:55:24 by adleau            #+#    #+#             */
/*   Updated: 2018/10/01 18:10:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global		g_global;

void				draw_image(void);

void				deactivate_buttons(GtkWidget *except)
{
	if (&(ADD_VIEW.sphere_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.sphere_button, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.plane_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.plane_button, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.cone_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cone_button, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.cylinder_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cylinder_button, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.obj_file_button) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.obj_file_button, GTK_STATE_FLAG_NORMAL, true);

}

void				validate_sphere(t_sphere *s)
{
	s->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin));
}

void				validate_plane(t_plane *p)
{
	p->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	p->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	p->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
}

void				validate_cone(t_cone *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
	c->angle = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.angle_spin)) / 360;
	c->infinite = gtk_switch_get_active(GTK_SWITCH(ADD_VIEW.infinite));
}

void				deactivate_buttons_from_tp(GtkWidget *except)
{
	if (&(ADD_VIEW.cube) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.cube, GTK_STATE_FLAG_NORMAL, true);
	if (&(ADD_VIEW.tetra) != &except)
		gtk_widget_set_state_flags(ADD_VIEW.tetra, GTK_STATE_FLAG_NORMAL, true);
}

void				validate_cylinder(t_cylinder *c)
{
	c->vector.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_x));
	c->vector.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_y));
	c->vector.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.vector_z));
	c->radius = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin));
	c->infinite = gtk_switch_get_active(GTK_SWITCH(ADD_VIEW.infinite));
}

void				validate_cube(void)
{
	set_cube(ADD_VIEW.sw.o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)) * 2, ADD_VIEW.sw.o);
}


void				validate_tetra(void)
{
	set_tetrahedron(ADD_VIEW.sw.o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), ADD_VIEW.sw.o);
}

void				validate_same_obj(t_obj *o)
{
	if (o->type == 66)
		validate_cube();
	else if (o->type == 67)
		validate_tetra();
}

void				validate_from_file(char *path)
{
//	set_poly_obj(ADD_VIEW.sw.o->position, gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.scale_spin)), ADD_VIEW.sw.o, path);
	(void)path;
}

void				validate_poly_obj(t_obj *o)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ADD_VIEW.same)))
		validate_same_obj(o);
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ADD_VIEW.from_template)))
	{
		if (o->type == 6)
			validate_from_file(ADD_VIEW.obj_file_path);
		else if (o->type == 66)
			validate_cube();
		else if (o->type == 67)
			validate_tetra();
	}
}

void				redraw(bool display)
{
	draw_image();
	if (display == true)
	{
		if (PIXMAP)
			cairo_surface_destroy(PIXMAP);
		PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
		if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
			exit(1);
		cairo_surface_mark_dirty(PIXMAP);
		gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area), PIXMAP);
	}
}

void				validate_edit(t_obj *o)
{
	GdkRGBA			*c;

	if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
		exit(1);
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
	o->color.r = (unsigned char)(c->red * 255);
	o->color.g = (unsigned char)(c->green * 255);
	o->color.b = (unsigned char)(c->blue * 255);
	o->color.trans = (unsigned char)(c->alpha);
	o->position.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_x_spin));
	o->position.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_y_spin));
	o->position.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(ADD_VIEW.translate_z_spin));
	if (o->type == 1)
		validate_sphere((t_sphere*)o->obj);
	else if (o->type == 2)
		validate_plane((t_plane*)o->obj);
	else if (o->type == 3)
		validate_cone((t_cone*)o->obj);
	else if (o->type == 4)
		validate_cylinder((t_cylinder*)o->obj);
	else if (o->type == 6 || o->type / 10 == 6)
		validate_poly_obj(o);
	redraw(true);
}

static void			edit_sphere_view(t_sphere *s)
{
	GtkAdjustment	*adj_scale;

	deactivate_buttons(ADD_VIEW.sphere_button);
	gtk_widget_set_state_flags(ADD_VIEW.sphere_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(s->radius, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_spin, 1, 1, 3, 1);
}

void				open_poly_obj(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint					res;
	char					*dir;

	dialog = gtk_file_chooser_dialog_new ("Open File",
										  GTK_WINDOW(ADD_VIEW.win),
										  action,
										  "_Cancel",
										  GTK_RESPONSE_CANCEL,
										  "_Open",
										  GTK_RESPONSE_ACCEPT,
										  NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1);
	dir = getwd(dir);
//	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), ft_strjoin(dir, "/scenes"));
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		g_free(filename);
	}
	gtk_widget_destroy (dialog);
}


void				add_cube(void)
{
	deactivate_buttons_from_tp(ADD_VIEW.cube);
	gtk_widget_set_state_flags(ADD_VIEW.cube, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.sw.o->type = 66;
}

void				add_tetra(void)
{
	deactivate_buttons_from_tp(ADD_VIEW.tetra);
	gtk_widget_set_state_flags(ADD_VIEW.tetra, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.sw.o->type = 67;
}

static void			radio_toggle(GtkWidget *button, gpointer __attribute__((unused))data)
{
	if (button == ADD_VIEW.file_check)
	{
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
		{
			ADD_VIEW.file_opener = gtk_button_new_from_icon_name("document-open", GTK_ICON_SIZE_BUTTON);
			gtk_widget_set_tooltip_text(ADD_VIEW.file_opener, "Open obj File");
			gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.file_opener, 2, 7, 1, 1);
			g_signal_connect(G_OBJECT(ADD_VIEW.file_opener), "clicked", G_CALLBACK(open_poly_obj), NULL);
			gtk_widget_show_all(ADD_VIEW.win);
		}
		else
		{
			if (ADD_VIEW.file_opener)
			{
				gtk_widget_destroy(ADD_VIEW.file_opener);
				ADD_VIEW.file_opener = NULL;
			}
		}
	}
	if (button == ADD_VIEW.from_template)
	{
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
		{
			ADD_VIEW.cube = gtk_button_new();
			ADD_VIEW.cube_img = gtk_image_new_from_file("uiconfig/cube.png");
			gtk_widget_set_tooltip_text(ADD_VIEW.cube, "Cube");
			gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cube), ADD_VIEW.cube_img);
			gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.cube, 2, 6, 1, 1);
			g_signal_connect(G_OBJECT(ADD_VIEW.cube), "clicked", G_CALLBACK(add_cube), NULL);
			ADD_VIEW.tetra = gtk_button_new();
			ADD_VIEW.tetra_img = gtk_image_new_from_file("uiconfig/tetra.png");
			gtk_widget_set_tooltip_text(ADD_VIEW.tetra, "Tetrahedron");
			gtk_button_set_image(GTK_BUTTON(ADD_VIEW.tetra), ADD_VIEW.tetra_img);
			gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.tetra, 3, 6, 1, 1);
			g_signal_connect(G_OBJECT(ADD_VIEW.tetra), "clicked", G_CALLBACK(add_tetra), NULL);
			gtk_widget_show_all(ADD_VIEW.win);
		}
		else
		{
			if (ADD_VIEW.cube)
			{
				gtk_widget_destroy(ADD_VIEW.cube);
				ADD_VIEW.cube = NULL;
			}
			if (ADD_VIEW.tetra)
			{
				gtk_widget_destroy(ADD_VIEW.tetra);
				ADD_VIEW.tetra = NULL;
			}
		}
	}
}


static void			edit_poly_view(t_poly_obj __attribute__((unused))*p)
{
	GtkAdjustment	*adj_scale;

	deactivate_buttons(ADD_VIEW.obj_file_button);
	gtk_widget_set_state_flags(ADD_VIEW.obj_file_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(ADD_VIEW.sw.o->size, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_spin, 1, 1, 3, 1);
	ADD_VIEW.same = gtk_radio_button_new_with_label(NULL, "Current object");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.same, 0, 5, 2, 1);
	ADD_VIEW.from_template = gtk_radio_button_new_with_label(NULL, "From Template");
	gtk_radio_button_join_group(GTK_RADIO_BUTTON(ADD_VIEW.from_template), GTK_RADIO_BUTTON(ADD_VIEW.same));
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.from_template, 0, 6, 2, 1);
	ADD_VIEW.file_check = gtk_radio_button_new_with_label(NULL, "From File");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.file_check, 0, 7, 2, 1);
	g_signal_connect(G_OBJECT(ADD_VIEW.file_check), "toggled", G_CALLBACK(radio_toggle), NULL);
	g_signal_connect(G_OBJECT(ADD_VIEW.same), "toggled", G_CALLBACK(radio_toggle), NULL);
	g_signal_connect(G_OBJECT(ADD_VIEW.from_template), "toggled", G_CALLBACK(radio_toggle), NULL);
	gtk_radio_button_join_group(GTK_RADIO_BUTTON(ADD_VIEW.file_check), GTK_RADIO_BUTTON(ADD_VIEW.same));
}

static void			edit_plane_view(t_plane *p)
{
	GtkAdjustment	*adj;

	deactivate_buttons(ADD_VIEW.plane_button);
	gtk_widget_set_state_flags(ADD_VIEW.plane_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.vector_img = gtk_image_new_from_file("uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_img, 0, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_x, 1, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_y, 2, 1, 1, 1);
	adj = gtk_adjustment_new(p->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_z, 3, 1, 1, 1);
}

static void			edit_cone_view(t_cone *c)
{
	GtkAdjustment	*adj;
	GtkAdjustment	*adj_angle;

	deactivate_buttons(ADD_VIEW.cone_button);
	gtk_widget_set_state_flags(ADD_VIEW.cone_button,GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.vector_img = gtk_image_new_from_file("uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_img, 0, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_x, 1, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_y, 2, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_z, 3, 4, 1, 1);
	ADD_VIEW.inf_img = gtk_image_new_from_file("uiconfig/infinite.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.inf_img, 0, 5, 1, 1);
	ADD_VIEW.infinite = gtk_switch_new();
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.infinite, 1, 5, 1, 1);
	gtk_switch_set_state(GTK_SWITCH(ADD_VIEW.infinite), c->infinite);
	ADD_VIEW.angle_img = gtk_image_new_from_file("uiconfig/angle.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.angle_img, 0, 6, 1, 1);
	adj_angle = gtk_adjustment_new(c->angle * 360, 0, 360, 1, 1, 10);
	ADD_VIEW.angle_spin = gtk_spin_button_new(adj_angle, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.angle_spin, 1, 6, 1, 1);
}

static void			edit_cylinder_view(t_cylinder *c)
{
	GtkAdjustment	*adj_scale;
	GtkAdjustment	*adj;

	deactivate_buttons(ADD_VIEW.cylinder_button);
	gtk_widget_set_state_flags(ADD_VIEW.cylinder_button,GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ADD_VIEW.scale_img = gtk_image_new_from_file("uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(c->radius, 0, 1000, .5, 1, 10);
	ADD_VIEW.scale_spin = gtk_spin_button_new(adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.scale_spin, 1, 1, 3, 1);
	ADD_VIEW.vector_img = gtk_image_new_from_file("uiconfig/vector.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_img, 0, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.x, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_x = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_x, 1, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.y, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_y = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_y, 2, 4, 1, 1);
	adj = gtk_adjustment_new(c->vector.z, -1000, 1000, .5, 1, 10);
	ADD_VIEW.vector_z = gtk_spin_button_new(adj, 1, 4);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.vector_z, 3, 4, 1, 1);
	ADD_VIEW.inf_img = gtk_image_new_from_file("uiconfig/infinite.png");
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.inf_img, 0, 5, 1, 1);
	ADD_VIEW.infinite = gtk_switch_new();
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.infinite, 1, 5, 1, 1);
	gtk_switch_set_state(GTK_SWITCH(ADD_VIEW.infinite), c->infinite);
}

void				set_default_values(t_obj *o)
{
	if (o->type == 1)
		((t_sphere*)o->obj)->radius = 2;
	else if (o->type == 2)
	{
		((t_plane*)o->obj)->vector.x = 1;
		((t_plane*)o->obj)->vector.y = 1;
		((t_plane*)o->obj)->vector.z = 1;
	}
	else if (o->type == 3)
	{
		((t_cone*)o->obj)->vector.x = 1;
		((t_cone*)o->obj)->vector.y = 1;
		((t_cone*)o->obj)->vector.z = 1;
		((t_cone*)o->obj)->angle = (double)60 / 360;
		((t_cone*)o->obj)->infinite = true;
	}
	else if (o->type == 4)
	{
		((t_cylinder*)o->obj)->vector.x = 1;
		((t_cylinder*)o->obj)->vector.y = 1;
		((t_cylinder*)o->obj)->vector.z = 1;
		((t_cylinder*)o->obj)->radius = 2;
		((t_cylinder*)o->obj)->infinite = true;
	}
}

static void			actual_edit_view(t_obj *o)
{
	GtkAdjustment	*adj_mv;

	if (!(ADD_VIEW.translate_x_spin) && !(ADD_VIEW.translate_y_spin) && !(ADD_VIEW.translate_z_spin))
	{
		gtk_window_set_title(GTK_WINDOW(ADD_VIEW.win), "Edit Object");
		ADD_VIEW.translate_img = gtk_image_new_from_file("uiconfig/move.png");
		gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_img, 0, 3, 1, 1);
		adj_mv = gtk_adjustment_new(o->position.x, -1000, 1000, .5, 1, 10);
		ADD_VIEW.translate_x_spin = gtk_spin_button_new(adj_mv, 1, 4);
		gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_x_spin, 1, 3, 1, 1);
		adj_mv = gtk_adjustment_new(o->position.y, -1000, 1000, .5, 1, 10);
		ADD_VIEW.translate_y_spin = gtk_spin_button_new(adj_mv, 1, 4);
		gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_y_spin, 2, 3, 1, 1);
		adj_mv = gtk_adjustment_new(o->position.z, -1000, 1000, .5, 1, 10);
		ADD_VIEW.translate_z_spin = gtk_spin_button_new(adj_mv, 1, 4);
		gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.translate_z_spin, 3, 3, 1, 1);

		GdkRGBA	*c;

		if (!(c = (GdkRGBA*)malloc(sizeof(GdkRGBA))))
			exit(1);
		c->red = (gdouble)(o->color.r) / 255;
		c->green = (gdouble)(o->color.g) / 255;
		c->blue = (gdouble)(o->color.b) / 255;
		c->alpha = 1;
		ADD_VIEW.color = gtk_color_chooser_widget_new();
		gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(ADD_VIEW.color), c);
		gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.color, 0, 8, 4, 1);
		free(c);
	}
	if (o->type == -5)
	{
		o->type = 1;
		o->next = g_global.r->objects;
		g_global.r->objects = o;
		if (!(o->obj = (t_sphere*)malloc(sizeof(t_sphere))))
			exit(1);
		set_default_values(o);
	}
	if (o->type == 1)
		edit_sphere_view((t_sphere*)o->obj);
	else if (o->type == 2)
		edit_plane_view((t_plane*)o->obj);
	else if (o->type == 3)
		edit_cone_view((t_cone*)o->obj);
	else if (o->type == 4)
		edit_cylinder_view((t_cylinder*)o->obj);
	else if (o->type / 10 == 6 || o->type == 6)
		edit_poly_view((t_poly_obj*)o->obj);
}

void				create_object(t_obj *o, int type)
{
	t_obj			*tmp;

	if (!(tmp = (t_obj*)malloc(sizeof(t_obj))))
		exit(1);
	if (type == 1)
	{
		tmp->obj = (t_sphere*)malloc(sizeof(t_sphere));
		tmp->type = 1;
	}
	else if (type == 2)
	{
		tmp->obj = (t_plane*)malloc(sizeof(t_plane));
		tmp->type = 2;
	}
	else if (type == 3)
	{
		tmp->obj = (t_cone*)malloc(sizeof(t_cone));
		tmp->type = 3;
	}
	else if (type == 4)
	{
		tmp->obj = (t_cylinder*)malloc(sizeof(t_cylinder));
		tmp->type = 4;
	}
	else if (type == 6 || type / 10 == 6)
	{
		tmp->obj = (t_poly_obj*)malloc(sizeof(t_poly_obj));
		tmp->type = 6;
	}
	set_default_values(tmp);
	free(o->obj);
	o->type = tmp->type;
	o->obj = tmp->obj;
}

void				destroy_interface_for_type(int type)
{
	if (type == 1 || type == 4)
	{
		gtk_widget_destroy(ADD_VIEW.scale_img);
		gtk_widget_destroy(ADD_VIEW.scale_spin);
	}
	if (type == 2 || type == 3 || type == 4)
	{
		gtk_widget_destroy(ADD_VIEW.vector_x);
		gtk_widget_destroy(ADD_VIEW.vector_y);
		gtk_widget_destroy(ADD_VIEW.vector_z);
		gtk_widget_destroy(ADD_VIEW.vector_img);
	}
	if (type == 3 || type == 4)
	{
		if (type == 3)
		{
			gtk_widget_destroy(ADD_VIEW.angle_img);
			gtk_widget_destroy(ADD_VIEW.angle_spin);
		}
		gtk_widget_destroy(ADD_VIEW.infinite);
		gtk_widget_destroy(ADD_VIEW.inf_img);
	}
	if (type == 6 || type / 10 == 6)
	{
		gtk_widget_destroy(ADD_VIEW.scale_img);
		gtk_widget_destroy(ADD_VIEW.scale_spin);
		gtk_widget_destroy(ADD_VIEW.file_check);
		gtk_widget_destroy(ADD_VIEW.same);
		gtk_widget_destroy(ADD_VIEW.from_template);
		gtk_widget_destroy(ADD_VIEW.cube);
		gtk_widget_destroy(ADD_VIEW.cube_img);
		gtk_widget_destroy(ADD_VIEW.tetra);
		gtk_widget_destroy(ADD_VIEW.tetra_img);
	}
}

void				switch_type(GtkButton *button)
{
	t_obj			*o;
	int				type;

	type = ADD_VIEW.sw.o->type;
	o = ADD_VIEW.sw.o;
	destroy_interface_for_type(o->type);
	if (button == GTK_BUTTON(ADD_VIEW.sphere_button))
	{
		ADD_VIEW.sw.type = 1;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.plane_button))
	{
		ADD_VIEW.sw.type = 2;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.cone_button))
	{
		ADD_VIEW.sw.type = 3;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.cylinder_button))
	{
		ADD_VIEW.sw.type = 4;
	}
	else if (button == GTK_BUTTON(ADD_VIEW.obj_file_button))
		ADD_VIEW.sw.type = 6;
	create_object(o, ADD_VIEW.sw.type);
	if (o)
		actual_edit_view(o);
	gtk_widget_show_all(ADD_VIEW.win);
	return ;
}

void				handle_edit_validation(t_obj *o)
{
	int		r;

	r = gtk_dialog_run(GTK_DIALOG(ADD_VIEW.win));

	if (r == GTK_RESPONSE_ACCEPT)
	{
		validate_edit(o);
		gtk_widget_destroy(ADD_VIEW.win);
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		draw_image();
		gtk_widget_destroy(ADD_VIEW.win);
	}
}

void				edit_win(t_obj *o)
{
	GtkWidget		*content_area;

	init_add_view();
	ADD_VIEW.sphere_img = gtk_image_new_from_file("uiconfig/sphere.png");
	ADD_VIEW.plane_img = gtk_image_new_from_file("uiconfig/plane.png");
	ADD_VIEW.cone_img = gtk_image_new_from_file("uiconfig/cone.png");
	ADD_VIEW.cylinder_img = gtk_image_new_from_file("uiconfig/cylinder.png");
	ADD_VIEW.obj_file_img = gtk_image_new_from_file("uiconfig/poly_obj.png");
	ADD_VIEW.win = gtk_dialog_new_with_buttons("Edit Object",
														 GTK_WINDOW(GTKMGR.ui.main_view.win),
														 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
														 "_OK",
														 GTK_RESPONSE_ACCEPT,
														 "_Cancel",
														 GTK_RESPONSE_REJECT,
														 NULL);
	gtk_window_set_transient_for(GTK_WINDOW(ADD_VIEW.win), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(ADD_VIEW.win), GTK_WIN_POS_MOUSE);
	ADD_VIEW.sw.o = o;
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(ADD_VIEW.win));
	ADD_VIEW.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), ADD_VIEW.grid);
	ADD_VIEW.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(ADD_VIEW.grid), ADD_VIEW.buttonbox, 0, 0, 4, 1);
	ADD_VIEW.sphere_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.sphere_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.sphere_button, "Sphere");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.sphere_button), ADD_VIEW.sphere_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.sphere_button);
	ADD_VIEW.plane_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.plane_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.plane_button, "Plane");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.plane_button), ADD_VIEW.plane_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.plane_button);
	ADD_VIEW.cone_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.cone_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.cone_button, "Cone");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cone_button), ADD_VIEW.cone_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.cone_button);
	ADD_VIEW.cylinder_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.cylinder_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.cylinder_button, "Cylinder");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.cylinder_button), ADD_VIEW.cylinder_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.cylinder_button);
	ADD_VIEW.obj_file_button = gtk_button_new();
	g_signal_connect(G_OBJECT(ADD_VIEW.obj_file_button), "clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(ADD_VIEW.obj_file_button, "Obj File");
	gtk_button_set_image(GTK_BUTTON(ADD_VIEW.obj_file_button), ADD_VIEW.obj_file_img);
	gtk_container_add(GTK_CONTAINER(ADD_VIEW.buttonbox), ADD_VIEW.obj_file_button);
	actual_edit_view(o);
	gtk_widget_show_all(ADD_VIEW.win);
	handle_edit_validation(o);
}
