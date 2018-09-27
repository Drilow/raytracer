/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:01 by adleau            #+#    #+#             */
/*   Updated: 2018/09/27 12:21:23 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr

extern t_global		g_global;

void				draw_image(void);
void				handle_main_view(void);

int					check_png(char *s)
{
	int				i;

	i = -1;
	while (s[++i])
		;
	i -= 4;
	if (ft_strcmp(s + i, ".png"))
		return (0);
	return (1);
}

void				export_view(void)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;
	char			*dir;

	dialog = gtk_file_chooser_dialog_new ("Export",
										  GTK_WINDOW(GTKMGR.ui.main_view.win),
										  action,
										  "_Cancel",
										  GTK_RESPONSE_CANCEL,
										  "_Export",
										  GTK_RESPONSE_ACCEPT,
										  NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1);
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), ft_strjoin(dir, "/screens"));
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		if (!check_png(filename))
			cairo_surface_write_to_png(PIXMAP, ft_strjoin(filename, ".png"));
		else
			cairo_surface_write_to_png(PIXMAP, filename);
		g_free (filename);
	}
	gtk_widget_destroy (dialog);

}

void			init_rt(void);

void			open_file(void)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	char *dir;

	dialog = gtk_file_chooser_dialog_new ("Open File",
										  GTK_WINDOW(g_global.base_view.win),
										  action,
										  "_Cancel",
										  GTK_RESPONSE_CANCEL,
										  "_Open",
										  GTK_RESPONSE_ACCEPT,
										  NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1);
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), ft_strjoin(dir, "/scenes"));
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	init_rt();
	init_gtk_variables();
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		if (!parse(filename))
			usage("Error : invalid argument.", 1);
		g_free (filename);
	}
	handle_main_view();
	gtk_widget_destroy (dialog);
}

void				handle_drawing(void);

void				outline_obj(t_obj *o)
{
	int				x;
	int				y;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			if (g_global.r->checker[y][x] == o)
			{
				if (g_global.r->checker[y - 1][x] != o && y - 1 >= 0)
				{
					draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
					draw_px(GTKMGR.buf, x, y - 1, ft_rgb(255, 0, 0, 0));
				}
				if (g_global.r->checker[y + 1][x] != o && y + 1 < WIN_H)
				{
					draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
					draw_px(GTKMGR.buf, x, y + 1, ft_rgb(255, 0, 0, 0));
				}
				if (g_global.r->checker[y][x - 1] != o && x - 1 >= 0)
				{
					draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
					draw_px(GTKMGR.buf, x - 1, y, ft_rgb(255, 0, 0, 0));
				}
				if (g_global.r->checker[y][x + 1] != o && x + 1 < WIN_W)
				{
					draw_px(GTKMGR.buf, x, y, ft_rgb(255, 0, 0, 0));
					draw_px(GTKMGR.buf, x + 1, y, ft_rgb(255, 0, 0, 0));
				}
			}
		}
	}
	if (PIXMAP)
		cairo_surface_destroy(PIXMAP);
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit(1);
	cairo_surface_mark_dirty(PIXMAP);
	gtk_image_set_from_surface(GTK_IMAGE(GTKMGR.ui.main_view.render_area), PIXMAP);
}

static gboolean		clicked(GtkWidget __attribute__((unused))*widget, GdkEventButton *event, gpointer __attribute__((unused))data)
{
	if (event->button == 1)
	{
		if (g_global.r->checker[(int)event->y][(int)event->x])
		{
			g_global.r->selected_obj = g_global.r->checker[(int)event->y][(int)event->x];
			if ((gtk_widget_get_state_flags(GTKMGR.ui.main_view.select_button) & GTK_STATE_FLAG_CHECKED))
			{
				outline_obj(g_global.r->selected_obj);
				edit_win(g_global.r->selected_obj);
			}
		}
	}
	return (true);
}

void				free_poly(t_poly_obj *p)
{
	(void)p;
}

	void init_rt(void);

void				destroy_scene(void)
{
	t_obj			*to_free;
	t_obj			*tmp;

	init_rt();
	to_free = g_global.r->objects;
	while (to_free)
	{
		tmp = to_free->next;
		if (to_free->type == 6)
			free_poly((t_poly_obj*)to_free->obj);
		else if (to_free->obj)
		{
			free(to_free->obj);
			to_free->obj = NULL;
		}
		if (to_free)
		{
			free(to_free);
			to_free = NULL;
		}
	}
}

void				handle_drawing(void)
{
	if (!(GTKMGR.buf = malloc(sizeof(unsigned char) * (WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W)))))
		exit(1);
	draw_image();
	if (PIXMAP)
	{
		cairo_surface_destroy(PIXMAP);
	}
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit(1);
	cairo_surface_mark_dirty(PIXMAP);
	GTKMGR.ui.main_view.render_area = gtk_image_new_from_surface(PIXMAP);
	GTKMGR.ui.main_view.event_box = gtk_event_box_new();
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.main_view.grid), GTKMGR.ui.main_view.event_box, 0, 1, 1, 1);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.event_box), GTKMGR.ui.main_view.render_area);
}


void				add_view(void)
{
	t_obj			*o;

	if (!(o = (t_obj*)malloc(sizeof(t_obj))))
		exit(1);
	o->type = -5;
	edit_win(o);
}


void				do_nothing(void)
{
	;
}

void				select_cb(void)
{
	if (!(gtk_widget_get_state_flags(GTKMGR.ui.main_view.select_button) & GTK_STATE_FLAG_CHECKED))
	{
		gtk_widget_set_state_flags(GTKMGR.ui.main_view.select_button, GTK_STATE_FLAG_CHECKED, false);
		g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.event_box),
						 "button_press_event",
						 G_CALLBACK(clicked),
						 GTKMGR.ui.main_view.render_area);
	}
	else
	{
		gtk_widget_unset_state_flags(GTKMGR.ui.main_view.select_button, GTK_STATE_FLAG_CHECKED);
		g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.event_box),
						 "button_press_event",
						 do_nothing, NULL);
//		GTKMGR.editmode = 0;
	}
}

void				handle_main_view(void)
{
	GTKMGR.ui.main_view.add_img = gtk_image_new_from_file("uiconfig/plus-sign-in-a-black-circle.png");
	GTKMGR.ui.main_view.filters_img = gtk_image_new_from_file("uiconfig/filter.png");
	GTKMGR.ui.main_view.select_img = gtk_image_new_from_file("uiconfig/new-file.png");
	GTKMGR.ui.main_view.export_img = gtk_image_new_from_file("uiconfig/scale-symbol.png");
	GTKMGR.ui.main_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.main_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.main_view.win), "raytracer");
	GTKMGR.ui.main_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.win), GTKMGR.ui.main_view.grid);
	GTKMGR.ui.main_view.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.grid), GTKMGR.ui.main_view.buttonbox);
	GTKMGR.ui.main_view.add_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.add_button, "add object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.add_button), "clicked", G_CALLBACK(add_view), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.add_button), GTKMGR.ui.main_view.add_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.add_button);
	GTKMGR.ui.main_view.filters_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.filters_button, "filters");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.filters_button), "clicked", G_CALLBACK(filter_win), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.filters_button), GTKMGR.ui.main_view.filters_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.filters_button);
	GTKMGR.ui.main_view.select_button = gtk_button_new();
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.select_button, "select object");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.select_button), "clicked", G_CALLBACK(select_cb), NULL);
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.select_button), GTKMGR.ui.main_view.select_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.select_button);
	GTKMGR.ui.main_view.export_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.export_button), GTKMGR.ui.main_view.export_img);
	gtk_widget_set_tooltip_text(GTKMGR.ui.main_view.export_button, "export to png format");
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.export_button), "clicked", G_CALLBACK(export_view), NULL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.export_button);
	handle_drawing();
	gtk_widget_show_all(GTKMGR.ui.main_view.win);
}

void				handle_base_view(void)
{
	g_global.base_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(g_global.base_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(g_global.base_view.win), "raytracer");
	g_signal_connect(G_OBJECT(g_global.base_view.win), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_global.base_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(g_global.base_view.win), g_global.base_view.grid);
	g_global.base_view.open_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.open_button), "Open Scene");
	g_signal_connect(G_OBJECT(g_global.base_view.open_button), "clicked", G_CALLBACK(open_file), NULL);
	g_global.base_view.new_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.new_button), "New Scene");
	g_signal_connect(G_OBJECT(g_global.base_view.new_button), "clicked", G_CALLBACK(handle_main_view), NULL);
	g_global.base_view.exit_button = gtk_button_new_from_icon_name("application-exit", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.exit_button), "Exit");
	gtk_button_set_always_show_image(GTK_BUTTON(g_global.base_view.exit_button), true);
	g_signal_connect(G_OBJECT(g_global.base_view.exit_button), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid), g_global.base_view.open_button, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid), g_global.base_view.new_button, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid), g_global.base_view.exit_button, 0, 1, 2, 1);
	gtk_widget_show_all(g_global.base_view.win);
}

static void			init_base_view(void)
{
	g_global.base_view.win = NULL;
	g_global.base_view.grid = NULL;
	g_global.base_view.open_button = NULL;
	g_global.base_view.new_button = NULL;
	g_global.base_view.exit_button = NULL;
}

void				handle_ui(void)
{
	handle_base_view();
}

void				init_gtk(int ac, char **av)
{
	init_base_view();
//	init_gtk_variables();
	gtk_init(&ac, &av);
	handle_ui();
	gtk_main();
}
