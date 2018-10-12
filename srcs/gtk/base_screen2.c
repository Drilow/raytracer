/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:11 by adleau            #+#    #+#             */
/*   Updated: 2018/10/12 17:02:49 by adleau           ###   ########.fr       */
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

void			on_key_press(GtkWidget *w, GdkEventKey *event)
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

void			dialog_keyhook(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
		gtk_widget_destroy(w);
	else
		return ;
}

void			end_open(GtkWidget *dialog)
{
	char					*filename;
	GtkFileChooser			*chooser;

	chooser = GTK_FILE_CHOOSER(dialog);
	filename = gtk_file_chooser_get_filename(chooser);
	if (!parse(filename))
		usage("Error : invalid argument.", 1);
	g_free(filename);
	handle_main_view();
}

void			open_file(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*dir;

	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File",
	GTK_WINDOW(g_global.base_view.win), action, "_Cancel",
	GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1);
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
	ft_strjoin(dir, "/scenes"));
	init_rt();
	init_gtk_variables();
	g_signal_connect(G_OBJECT(dialog), "key-press-event",
	G_CALLBACK(dialog_keyhook), NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
		end_open(dialog);
	else
		g_object_unref(dialog);
}
