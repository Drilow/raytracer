/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:01 by adleau            #+#    #+#             */
/*   Updated: 2018/07/22 15:27:00 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#define MAIN_WIN g_global.gtk_mgr.main_win
#define BUTTONS g_global.gtk_mgr.grid.buttons

extern t_global		g_global;

static void			base_screen(GtkApplication *app, gpointer __attribute__((unused))user_data)
{
	MAIN_WIN = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(MAIN_WIN), "Raytracer");
	gtk_window_set_default_size(GTK_WINDOW(MAIN_WIN), WIN_W, WIN_H);
	g_global.gtk_mgr.grid.grid = gtk_grid_new();
	gtk_widget_set_halign(g_global.gtk_mgr.grid.grid, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(g_global.gtk_mgr.grid.grid, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(MAIN_WIN), g_global.gtk_mgr.grid.grid);
	if (!(BUTTONS = malloc(sizeof(t_gtk_buttons) * 3)))
		exit(1);
	BUTTONS[0].button = gtk_button_new_with_label("Open Scene");
	//open scene code
	gtk_grid_attach(GTK_GRID(g_global.gtk_mgr.grid.grid), BUTTONS[0].button, 0, 0, 1, 1);
	BUTTONS[1].button = gtk_button_new_with_label("New Scene");
	g_signal_connect_swapped(BUTTONS[1].button, "clicked", G_CALLBACK(main_screen), MAIN_WIN);
	gtk_grid_attach(GTK_GRID(g_global.gtk_mgr.grid.grid), BUTTONS[1].button, 1, 0, 1, 1);
	BUTTONS[2].button = gtk_button_new_with_label("Close");
	g_signal_connect_swapped(BUTTONS[2].button, "clicked", G_CALLBACK(gtk_widget_destroy), MAIN_WIN);
	gtk_grid_attach(GTK_GRID(g_global.gtk_mgr.grid.grid), BUTTONS[2].button, 0, 1, 2, 1);
	gtk_widget_show_all(MAIN_WIN);
}

void				init_gtk(int ac, char **av)
{
	GtkApplication	*app;
	int				status;

	app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (base_screen), NULL);
	status = g_application_run (G_APPLICATION (app), ac, av);
	g_object_unref (app);
}
