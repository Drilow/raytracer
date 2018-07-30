/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:01 by adleau            #+#    #+#             */
/*   Updated: 2018/07/30 07:42:58 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <parser/parser.h>
#define PIXMAP g_global.gtk_mgr.pixmap
#define BUILDER g_global.gtk_mgr.builder
#define WINDOWS g_global.gtk_mgr.windows
#define ACTIVE_WIN g_global.gtk_mgr.active_win

extern t_global		g_global;

void				exit_program(void)
{
	gtk_main_quit();
}

void				hide_win(GtkWidget *win)
{
	gtk_widget_hide(gtk_widget_get_toplevel(win));
}

void				clear_surface(void)
{
	cairo_t *cr;

	cr = cairo_create (PIXMAP);
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);

	cairo_destroy (cr);
}

#include <sdl_stuff/sdl_mgr.h>
void			draw_image(t_sdl_wrapper *e);

void				handle_drawing(void)
{
	GtkWidget		*draw_rt;
	cairo_t			*c;

	draw_rt = GTK_WIDGET(gtk_builder_get_object(BUILDER, "draw_area"));
	if (PIXMAP)
		cairo_surface_destroy(PIXMAP);
	PIXMAP = cairo_image_surface_create_for_data((unsigned char*)DATA->pixels, CAIRO_FORMAT_RGB24,
												WIN_W, WIN_H,
												cairo_format_stride_for_width(
												CAIRO_FORMAT_RGB24, WIN_W));

	draw_image(&(g_global.sdl_mgr));
	c = cairo_create(PIXMAP);
	cairo_paint(c);
//	clear_surface();

}

void				main_window(void)
{

	WINDOWS[MAIN_WIN].win = GTK_WIDGET(gtk_builder_get_object(BUILDER, "main_window"));
	handle_drawing();
//	draw_image(&(g_global.sdl_mgr));
	gtk_widget_show(WINDOWS[MAIN_WIN].win);
}

void				open_file(void)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",
										  GTK_WINDOW(WINDOWS[BASE_WIN].win),
										  action,
										  "_Cancel",
										  GTK_RESPONSE_CANCEL,
										  "_Open",
										  GTK_RESPONSE_ACCEPT,
										  NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
		printf("%s\n", filename);
		if (!parse(filename))
			usage("Error : invalid argument.", 1);
		main_window();
		g_free (filename);
	}

	gtk_widget_destroy (dialog);
}

void				handle_base_win_buttons(void)
{
	if (!(WINDOWS[BASE_WIN].buttons = malloc(sizeof(GtkWidget*) * 3)))
		exit(1);
	WINDOWS[BASE_WIN].buttons[0] = GTK_WIDGET(gtk_builder_get_object(BUILDER, "Open_Scene"));
	g_signal_connect(G_OBJECT(WINDOWS[BASE_WIN].buttons[0]), "clicked", G_CALLBACK(open_file), WINDOWS[BASE_WIN].win);
	WINDOWS[BASE_WIN].buttons[1] = GTK_WIDGET(gtk_builder_get_object(BUILDER, "New_scene"));
	g_signal_connect(G_OBJECT(WINDOWS[BASE_WIN].buttons[1]), "clicked", G_CALLBACK(open_file), WINDOWS[BASE_WIN].win);
	WINDOWS[BASE_WIN].buttons[2] = GTK_WIDGET(gtk_builder_get_object(BUILDER, "exit_program"));
	g_signal_connect(G_OBJECT(WINDOWS[BASE_WIN].buttons[2]), "clicked", G_CALLBACK(exit_program), WINDOWS[BASE_WIN].win);
}

void				window_handler(void)
{
	WINDOWS[BASE_WIN].win = GTK_WIDGET(gtk_builder_get_object(BUILDER, "base_window"));
	g_signal_connect(G_OBJECT(WINDOWS[BASE_WIN].win), "destroy", G_CALLBACK(exit_program), NULL);
	handle_base_win_buttons();
	WINDOWS[MAIN_WIN].win = GTK_WIDGET(gtk_builder_get_object(BUILDER, "main_window"));
	gtk_widget_show(WINDOWS[BASE_WIN].win);
}

void				init_gtk(int ac, char **av)
{
	GError			*error;

	ACTIVE_WIN = 0;
	error = NULL;
//	PIXMAP = NULL;
	gtk_init(&ac, &av);
	BUILDER = gtk_builder_new();
	if(!gtk_builder_add_from_file(BUILDER,"uiconfig/rt2.glade",&error))
    {
		g_warning("%s", error->message);
        g_free(error);
		exit(1);
    }
	if (!(WINDOWS = malloc(sizeof(t_window) * NB_WINDOWS)))
		exit(1);
	window_handler();
	gtk_main();
	g_object_unref(G_OBJECT(BUILDER));
}
