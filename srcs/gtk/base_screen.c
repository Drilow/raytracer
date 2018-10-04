/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:01 by adleau            #+#    #+#             */
/*   Updated: 2018/10/04 17:40:45 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view

extern t_global		g_global;

void				on_key_press(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
		gtk_widget_destroy(w);
	else if (event->keyval != GDK_KEY_Escape)
		return ;
	if (g_global.r && w == ADD_VIEW.win)
		draw_image();
	if (w == g_global.base_view.win && event->keyval == GDK_KEY_Escape)
		gtk_main_quit();
}

void			init_rt(void);

void			dialog_keyhook(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
		gtk_widget_destroy(w);
	else
		return ;
}

void			open_file(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint					res;
	char					*dir;

	dialog = gtk_file_chooser_dialog_new("Open File",
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
	init_rt();
	init_gtk_variables();
	g_signal_connect(G_OBJECT(dialog), "key-press-event", G_CALLBACK(dialog_keyhook), NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);

		if (!parse(filename))
			usage("Error : invalid argument.", 1);
		g_free(filename);
		handle_main_view();
	}
	else
		g_object_unref(dialog);
}

void				free_poly(t_poly_obj *p)
{
	(void)p;
}

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

void				handle_base_view(void)
{
	g_global.base_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(g_global.base_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(g_global.base_view.win), "raytracer");
	g_global.base_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(g_global.base_view.win), g_global.base_view.grid);
	g_global.base_view.open_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.open_button), "Open Scene");
	g_signal_connect(G_OBJECT(g_global.base_view.open_button), "clicked", G_CALLBACK(open_file), NULL);
	g_global.base_view.exit_button = gtk_button_new_from_icon_name("application-exit", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.exit_button), "Exit");
	gtk_button_set_always_show_image(GTK_BUTTON(g_global.base_view.exit_button), true);
	g_signal_connect(G_OBJECT(g_global.base_view.exit_button), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid), g_global.base_view.open_button, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid), g_global.base_view.exit_button, 0, 1, 2, 1);
	g_signal_connect(G_OBJECT(g_global.base_view.win), "key-press-event", G_CALLBACK(on_key_press), NULL);
	g_signal_connect(G_OBJECT(g_global.base_view.win), "delete-event", G_CALLBACK(handle_x_button), NULL);
/*	pbar = gtk_progress_bar_new();
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid), pbar, 0, 2, 2, 1);
*/	gtk_widget_show_all(g_global.base_view.win);
}

static void			init_base_view(void)
{
	g_global.base_view.win = NULL;
	g_global.base_view.grid = NULL;
	g_global.base_view.open_button = NULL;
	g_global.base_view.exit_button = NULL;
}

void				init_add_view(void);

void				handle_ui(void)
{
	handle_base_view();
}

void				init_gtk(int ac, char **av)
{
	init_base_view();
	g_global.r = NULL;
	gtk_init(&ac, &av);
	handle_ui();
	gtk_main();
}
