/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:01 by adleau            #+#    #+#             */
/*   Updated: 2018/08/07 13:00:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <parser/parser.h>
#define PIXMAP g_global.gtk_mgr.pixmap
#define GTKMGR g_global.gtk_mgr

extern t_global		g_global;

void			draw_image(t_sdl_wrapper *e);
void				handle_main_view(void);

void				export_view(void)
{
	cairo_surface_write_to_png(PIXMAP, "/tmp/test.png");
}

void				open_file(void)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",
										  GTK_WINDOW(GTKMGR.ui.picker_view.dialog),
										  action,
										  "_Cancel",
										  GTK_RESPONSE_CANCEL,
										  "_Open",
										  GTK_RESPONSE_ACCEPT,
										  NULL);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
		printf("%s\n", filename);
		if (!parse(filename))
			usage("Error : invalid argument.", 1);
		printf("MESCOUILLES\n");
		g_free (filename);
	}
	handle_main_view();
	gtk_widget_destroy (dialog);
}

void				handle_drawing(void)
{
	printf("aallo %p\n", g_global.r.objects);
	if (!(GTKMGR.buf = malloc(sizeof(unsigned char) * (WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W)))))
		exit(1);
	printf("a2llo\n");
	draw_image(&(g_global.sdl_mgr));
	PIXMAP = cairo_image_surface_create_for_data(GTKMGR.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H, cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(PIXMAP) != CAIRO_STATUS_SUCCESS)
		exit(1);
	printf("wow\n");
	cairo_surface_mark_dirty(PIXMAP);
	GTKMGR.ui.main_view.render_area = gtk_image_new_from_surface(PIXMAP);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.main_view.grid), GTKMGR.ui.main_view.render_area, 0, 1, 1, 1);
}

#include <libft.h>

void				handle_main_view(void)
{
	GTKMGR.ui.main_view.add_img = gtk_image_new_from_file("uiconfig/plus-sign-in-a-black-circle.png");
	GTKMGR.ui.main_view.filters_img = gtk_image_new_from_file("uiconfig/filter.png");
	GTKMGR.ui.main_view.select_img = gtk_image_new_from_file("uiconfig/select.png");
	GTKMGR.ui.main_view.edit_img = gtk_image_new_from_file("uiconfig/new-file.png");
	GTKMGR.ui.main_view.export_img = gtk_image_new_from_file("uiconfig/scale-symbol.png");
	GTKMGR.ui.main_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.main_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.main_view.win), "raytracer");
	GTKMGR.ui.main_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.win), GTKMGR.ui.main_view.grid);
	GTKMGR.ui.main_view.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.grid), GTKMGR.ui.main_view.buttonbox);
	GTKMGR.ui.main_view.add_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.add_button), GTKMGR.ui.main_view.add_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.add_button);
	GTKMGR.ui.main_view.filters_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.filters_button), GTKMGR.ui.main_view.filters_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.filters_button);
	GTKMGR.ui.main_view.select_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.select_button), GTKMGR.ui.main_view.select_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.select_button);
	GTKMGR.ui.main_view.edit_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.edit_button), GTKMGR.ui.main_view.edit_img);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.edit_button);
	GTKMGR.ui.main_view.export_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(GTKMGR.ui.main_view.export_button), GTKMGR.ui.main_view.export_img);
	g_signal_connect(G_OBJECT(GTKMGR.ui.main_view.export_button), "clicked", G_CALLBACK(export_view), NULL);
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.main_view.buttonbox), GTKMGR.ui.main_view.export_button);
//	if (g_global.r.objects != NULL)
	handle_drawing();
	gtk_widget_show_all(GTKMGR.ui.main_view.win);
}

void				handle_base_view(void)
{
	GTKMGR.ui.base_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(GTKMGR.ui.base_view.win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(GTKMGR.ui.base_view.win), "raytracer");
	g_signal_connect(G_OBJECT(GTKMGR.ui.base_view.win), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	GTKMGR.ui.base_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(GTKMGR.ui.base_view.win), GTKMGR.ui.base_view.grid);
	GTKMGR.ui.base_view.open_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(GTKMGR.ui.base_view.open_button), "Open Scene");
	g_signal_connect(G_OBJECT(GTKMGR.ui.base_view.open_button), "clicked", G_CALLBACK(open_file), NULL);
	GTKMGR.ui.base_view.new_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(GTKMGR.ui.base_view.new_button), "New Scene");
	g_signal_connect(G_OBJECT(GTKMGR.ui.base_view.new_button), "clicked", G_CALLBACK(handle_main_view), NULL);
	GTKMGR.ui.base_view.exit_button = gtk_button_new_from_icon_name("application-exit", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_label(GTK_BUTTON(GTKMGR.ui.base_view.exit_button), "Exit");
	gtk_button_set_always_show_image(GTK_BUTTON(GTKMGR.ui.base_view.exit_button), true);
	g_signal_connect(G_OBJECT(GTKMGR.ui.base_view.exit_button), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.base_view.grid), GTKMGR.ui.base_view.open_button, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.base_view.grid), GTKMGR.ui.base_view.new_button, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(GTKMGR.ui.base_view.grid), GTKMGR.ui.base_view.exit_button, 0, 1, 2, 1);
	gtk_widget_show_all(GTKMGR.ui.base_view.win);
}

void				handle_ui(void)
{
	handle_base_view();
}

void				init_gtk(int ac, char **av)
{
	init_gtk_variables();
	gtk_init(&ac, &av);
	handle_ui();
	gtk_main();
}
